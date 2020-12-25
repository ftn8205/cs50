import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

#pk_2177b0ba5b0b4be0968c628850fd253e 
# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    rows = db.execute("SELECT symbol, price, SUM(shares) AS shares_sum , SUM(total) AS total_sum FROM txnRecord WHERE userId = :userId GROUP BY symbol", userId=session["user_id"])
    cash = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id = session["user_id"])
    total = 0
    for row in rows:
        total = row["total_sum"] + total
        row["total_sum"] = usd(row["total_sum"])
    total = total + cash[0]["cash"]
    return render_template("index.html",rows = rows, cash = usd(cash[0]["cash"]), total = usd(total))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("must provide symbol", 400)
        if not request.form.get("shares"):
            return apology("must provide shares", 400)

        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))
        quote_result = lookup(symbol)
        if quote_result != None:
            name = quote_result["name"]
            price = quote_result["price"]
            total = shares * price

            userCash = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])
            if total > userCash[0]["cash"]:
                return apology("can't afford", 400)

            else:
                db.execute("INSERT INTO txnRecord (userId, name, symbol, shares, price, total) VALUES (?,?,?,?,?,?)",
                session["user_id"], name, symbol, shares, price, total)

                cash = userCash[0]["cash"] - total
                db.execute("UPDATE users SET cash = :cash WHERE id = :user_id", cash=cash, user_id=session["user_id"])

            return redirect("/")
        else:
            return apology("Invalid symbol", 400)
    else:
        return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    rows = db.execute("SELECT symbol, shares, price, txnTime FROM txnRecord WHERE userId = :user_id", user_id=session["user_id"])
    return render_template("history.html", rows=rows)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")
    else:
        if not request.form.get("symbol"):
            return apology("must provide symbol", 400)
        quote_result = lookup(request.form.get("symbol"))
        if quote_result != None:
            return render_template("quoted.html", name = quote_result["name"], symbol = quote_result["symbol"], price = quote_result["price"])
        else:
            return apology("Invalid symbol", 400)



@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        if not request.form.get("username"):
            return apology("must provide username", 403)
        if not request.form.get("password"):
            return apology("must provide password", 403)
        if not request.form.get("confirmation"):
            return apology("must provide confirmation", 403)
        if request.form.get("password") != request.form.get("confirmation"):
            return apology("password is inconsistent", 403)
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))
        if len(rows) != 0:
            return apology("The username is already taken", 409)
        else:
            # insert
            db.execute("INSERT INTO users (username, hash) VALUES (?,?)",
                    request.form.get("username"), generate_password_hash(request.form.get("password")))
            rows = db.execute("SELECT * FROM users WHERE username = :username",
                    username=request.form.get("username"))

            session["user_id"] = rows[0]["id"]
            # redirect
            return redirect("/")
    else:
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("must provide symbol")
        if not request.form.get("shares"):
            return apology("must provide shares")

        query_result = lookup(request.form.get("symbol"))

        if not query_result:
            return apology("invalid symbol", 400)

        rows = db.execute("SELECT SUM(shares) AS 'shares_sum' FROM txnRecord WHERE userId = :userId GROUP BY symbol HAVING symbol = :symbol", userId=session["user_id"], symbol=query_result["symbol"])

        if int(request.form.get("shares")) > rows[0]["shares_sum"]:
            return apology("shares is not enough", 403)
        else:
            shares = -int(request.form.get("shares"))
            total = shares * query_result["price"]

            db.execute("INSERT INTO txnRecord (userId, symbol, name, shares, price, total) VALUES (?,?,?,?,?,?)",
                        session["user_id"], query_result["symbol"], query_result["name"], shares, query_result["price"], total)
        user_data = db.execute("SELECT * From users WHERE id = :userId", userId = session["user_id"])
        cash = user_data[0]["cash"] - total
        db.execute("UPDATE users SET cash = :cash WHERE id = :userId", cash=cash, userId=session["user_id"])
        return redirect("/")
    else:
        rows = db.execute("SELECT symbol FROM txnRecord WHERE userId = :user_id GROUP BY symbol", user_id=session["user_id"])
        return render_template("sell.html", rows = rows)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)

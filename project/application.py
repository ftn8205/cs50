from flask import Flask
from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
from helpers import apology, login_required

app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

db = SQL("sqlite:///blog.db")

@app.route("/home")
def index():
    """Show portfolio of stocks"""
    print(session['user_id'])
    rows = db.execute("SELECT * FROM users WHERE id = :id",
                          id=session['user_id'])

    return render_template("home.html",name = rows[0]['username'])

@app.route("/about")
def about():
    return render_template("about.html")

@app.route("/blog", methods=["GET", "POST"])
def blog():
    if request.method == "POST":
        if not request.form.get("title"):
            return apology("must provide title", 403)
        if not request.form.get("content"):
            return apology("must provide content", 403)
        title = request.form.get("title");
        content = request.form.get("content");
        db.execute("INSERT INTO article (title, content) VALUES (?,?)",
                title, content)

        return redirect("/blog")
    else:
        rows = db.execute("SELECT * FROM article")

    return render_template("blog.html", articles = rows)

@app.route("/new_post")
def new_post():
    return render_template("new_post.html")

@app.route("/detail")
def detail():
    id = request.args.get('id')
    article = db.execute("SELECT * FROM article WHERE id= :id", id=id)
    return render_template("detail.html", article = article)

@app.route("/delete")
def delete():
    id = request.args.get('id')
    article = db.execute("DELETE FROM article WHERE id= :id", id=id)

    return redirect("/blog")

@app.route("/edit", methods=["GET", "POST"])
def edit():
    if request.method == "POST":
        id = request.args.get('id');
        title = request.form.get("title");
        content = request.form.get("content");
        db.execute("UPDATE article SET title = :title, content = :content WHERE id = :id",
                id = id, title = title, content =content)

        return redirect("/blog")

    else:
        id = request.args.get('id')
        article = db.execute("SELECT * FROM article WHERE id= :id", id=id)

        return render_template("edit_post.html", article=article)


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
            return redirect("/home")
    else:
        return render_template("register.html")


@app.route("/", methods=["GET", "POST"])
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
        return redirect("/home")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("signin.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")

def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)

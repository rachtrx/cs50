import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    if session.get("user_id") is None:
        return redirect("/login")
    stocks = db.execute("SELECT symbol, SUM(shares) FROM records WHERE id = ? GROUP BY symbol HAVING SUM(shares) > 0", session["user_id"])
    getUser = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
    cash = getUser[0]["cash"]
    total = 0
    for stock in stocks:
        symbol = stock["symbol"].upper()
        stockLookup = lookup(symbol)
        stock["name"] = stockLookup["name"]
        # why doesn't stock["price"] = usd(stockLookup["price"]) work???
        price = stockLookup["price"]
        stock["price"] = usd(price)
        value = price * stock["SUM(shares)"]
        stock["total"] = usd(value)
        total += value
    total += cash
    return render_template("index.html", stocks=stocks, cash=usd(cash), total=usd(total))

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")
    else:
        # incomplete input
        symbol = request.form.get("symbol")
        rawShares = request.form.get("shares")
        if symbol == "" or rawShares == "":
            return apology("INCOMPLETE INPUT", 400)

        # not a number
        elif not rawShares.isdigit():
            return apology("NOT A NUMBER", 400)

        # negative shares
        shares = int(rawShares)
        if shares < 1:
            return apology("INVALID SHARES", 400)

        # not a stock
        if lookup(symbol) == None:
            return apology("INVALID SYMBOL", 400)
        else:
            getUser = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
            if len(getUser) != 1:
                return apology("USERNAME ERROR", 400)
            availableFunds = getUser[0]["cash"]
            price = lookup(symbol)["price"]
            cost = shares * price
            if cost > availableFunds:
                return apology("INSUFFICIENT FUNDS", 400)
            else:
                db.execute("INSERT INTO records (id, symbol, shares, price) VALUES (?, ?, ?, ?)", session["user_id"], symbol.upper(), shares, usd(price))
                db.execute("UPDATE users SET cash = ? WHERE id = ?", availableFunds - cost, session["user_id"])
                return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute("SELECT * FROM records WHERE id = ?", session["user_id"])
    return render_template("history.html", transactions=transactions)


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
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

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
    if request.method == 'GET':
        return render_template("quote.html")
    else:
        symbol = request.form.get("symbol")
        if lookup(symbol) == None:
            return apology("INVALID SYMBOL", 400)
        else:
            name = lookup(symbol)["name"]
            price = usd(lookup(symbol)["price"])
            return render_template("quoted.html", name = name, symbol = symbol.upper(), price = price)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "GET":
        return render_template("register.html")
    # if POST request:
    username = request.form.get("username")
    password = request.form.get("password")
    confirm = request.form.get("confirmation")
    if username == "" or password == "" or confirm == "":
        return apology("Username cannot be blank", 400)
    # reject username if it is already in the database
    checkUser = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
    if len(checkUser) != 0:
        return apology("Username already exists", 400)
    # reject password if the confirmation does not match
    elif password != confirm:
        return apology("Password does not match", 400)
    db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, generate_password_hash(password))
    return redirect("/login")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    stocks = db.execute("SELECT symbol, SUM(shares) > 0 FROM records WHERE id = ? GROUP BY symbol HAVING SUM(shares) > 0", session["user_id"])
    if request.method == "GET":
        return render_template("sell.html", stocks=stocks)
    else:
        symbol = request.form.get("symbol")
        rawShares = request.form.get("shares")
        # incomplete input. Not sure why symbol is None and shares is ""...
        if symbol == None or rawShares == "":
            return apology("INCOMPLETE INPUT", 400)
        # not a number
        if not rawShares.isdigit():
            return apology("NOT A NUMBER", 400)
        # negative shares
        shares = int(rawShares)
        if shares < 1:
            return apology("INVALID SHARES", 400)
        # check if you really own it
        stockOwned = False
        for stock in stocks:
            if symbol.upper() == stock["symbol"]:
                stockOwned = True
        if stockOwned == False:
            return apology("NOT OWNED", 400)

        getUser = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
        if len(getUser) != 1:
            return apology("USERNAME ERROR", 400)
        getShares = db.execute("SELECT SUM(shares) FROM records WHERE id = ? AND symbol = ?", session["user_id"], symbol)
        ownedShares = getShares[0]["SUM(shares)"]
        if shares > ownedShares:
            return apology("TOO MANY SHARES", 400)
        else:
            price = lookup(symbol)["price"]
            value = shares * price
            db.execute("INSERT INTO records (id, symbol, shares, price) VALUES (?, ?, ?, ?)", session["user_id"], symbol.upper(), 0 - shares, usd(price))
            db.execute("UPDATE users SET cash = ? WHERE id = ?", getUser[0]["cash"] + value, session["user_id"])
            return redirect("/")

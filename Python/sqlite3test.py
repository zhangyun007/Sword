import sqlite3

# test.db is a file in the working directory.
conn = sqlite3.connect("test.db")
c = conn.cursor()

# create tables
c.execute('''CREATE TABLE category
      (id int primary key, sort int, name text)''')
	  
c.execute('''CREATE TABLE book
      (id int primary key, 
       sort int, 
       name text, 
       price real, 
       category int,
       FOREIGN KEY (category) REFERENCES category(id))''')
	   
conn.commit()


books = [(1, 1, 'Cook Recipe', 3.12, 1),
            (2, 3, 'Python Intro', 17.5, 2),
            (3, 2, 'OS Intro', 13.6, 2) ]

c.execute("INSERT INTO category VALUES (1, 1, 'kitchen')")

c.execute("INSERT INTO category VALUES (2, 2, 'computer')")

# execute multiple commands
c.executemany('INSERT INTO book VALUES (? , ? , ?, ?, ?)', books)

conn.commit()


# retrieve one record
c.execute('SELECT name FROM category ORDER BY sort')
print(c.fetchone())
print(c.fetchone())

# retrieve all records as a list

c.execute('SELECT * FROM book WHERE book.category=1')
print(c.fetchall())

# iterate through the records
for row in c.execute('SELECT name, price FROM book ORDER BY sort'):
    print(row)

conn.commit()


conn.close()

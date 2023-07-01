import csv
from cs50 import SQL

def main():

    db = SQL("sqlite:///roster.db")

    with open("students.csv", "r") as file:
        reader = csv.DictReader(file)

        student_names = []
        house_names = []

        for row in reader:

            id = row['id']
            name = row['student_name']
            house = row['house']
            head = row['head']

            student_id = insert_student(student_names, id, name, db)
            house_id = insert_house(house_names, house, head, db)
            if (student_id != None and house_id != None):
                insert_assignment(student_id, house_id, db)

def insert_student(student_names, id, name, db):
    if name in student_names:
        return None
    else:
        student_names.append(name)
        db.execute("INSERT INTO new_students (id, student_name) VALUES (?, ?);", id, name)
    return id

def insert_house(house_names, house, head, db):
    if house in house_names:
        house_id_ = house_names.index(house) + 1
        return house_id_
    elif house not in house_names:
        house_names.append(house)
        house_id_ = house_names.index(house) + 1
        db.execute("INSERT INTO houses (id, house, head) VALUES (?, ?, ?);", house_id_, house, head)
        return house_id_
    else:
        return None

def insert_assignment(student_id, house_id, db):
    db.execute("INSERT INTO assignments (student_id, house_id) VALUES (?, ?);", student_id, house_id)
    return

if __name__ == "__main__":
    main()

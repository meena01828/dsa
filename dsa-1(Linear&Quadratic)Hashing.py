size = 10
hashtable = [0] * size
hashtable1 = [0] * size

def hash_v(num):
    index = num % size
    start = index
    while hashtable[index] != 0:
        index = (index + 1) % size
        if index == start:
            print("Error: Hashtable is full for linear probing.")
            return
    hashtable[index] = num

def quadratic_v(num):
    index = num % size
    k = 1
    start = index
    while hashtable1[index] != 0:
        index = (num % size + k * k) % size
        k += 1
        if k > size:
            print("Error: Hashtable is full for quadratic probing.")
            return
        if index == start:
            break
    hashtable1[index] = num

def find(num, hash_table, method="linear"):
    index = num % size
    start = index
    k = 1

    while hash_table[index] != 0:
        if hash_table[index] == num:
            print(f"Found: {num} at index {index}")
            return
        if method == "linear":
            index = (index + 1) % size
        elif method == "quadratic":
            index = (num % size + k * k) % size
            k += 1
            if k > size:
                break
        if index == start:
            break
    print(f"Not found: {num}")

def main():
    while True:
        print("\n1. Linear Probing")
        print("2. Quadratic Probing")
        print("3. Find Element")
        print("4. Exit")

        ch = int(input("Enter choice: "))

        if ch == 1:
            n = int(input("Enter total elements: "))
            for j in range(n):
                h = int(input(f"Enter phone number {j + 1}: "))
                hash_v(h)
            print("Hashtable using linear probing:", hashtable)

        elif ch == 2:
            m = int(input("Enter total elements: "))
            for j in range(m):
                q = int(input(f"Enter phone number {j + 1}: "))
                quadratic_v(q)
            print("Hashtable using quadratic probing:", hashtable1)

        elif ch == 3:
            n = int(input("Enter number to find: "))
            print("1. Search in Linear Probing Table")
            print("2. Search in Quadratic Probing Table")
            table_choice = int(input("Enter your choice: "))

            if table_choice == 1:
                find(n, hashtable, "linear")
            elif table_choice == 2:
                find(n, hashtable1, "quadratic")
            else:
                print("Invalid table choice.")

        elif ch == 4:
            print("End of Program")
            break

        else:
            print("Enter a valid choice.")

if __name__ == "__main__":
    main()

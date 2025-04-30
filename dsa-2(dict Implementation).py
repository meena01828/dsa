size = 10 
hash_table = {} 
 
def addList(table, size): 
    for i in range(size): 
        table[i] = [] 
    return table 
 
def insert_lst(n, key, val, table): 
    idx = val % n 
    lst = [key, val] 
    table[idx].append(lst) 
    return table 
 
def delete_key(key, table): 
    for i in table: 
        for j in table[i]: 
            if key == j[0]: 
                table[i].remove(j) 
                return f"Key '{key}' deleted successfully." 
    return f"Key '{key}' not found." 
 
def find_key(key, table): 
    for i in table: 
        for j in table[i]: 
            if j[0] == key: 
                return f"Key '{key}' found with value: {j[1]}" 
    return f"Key '{key}' not found." 
hash_table = addList(hash_table, size) 
 
def main(): 
    while True: 
        print("\nDictionary Implementation") 
        print("1. Insert an element") 
        print("2. Delete an element") 
        print("3. Find a key") 
        print("4. Exit") 
         
        try: 
            choice = int(input("Enter your choice: ")) 
        except ValueError: 
            print("Invalid input! Please enter a number.") 
            continue 
 
        if choice == 1: 
            key = input("Enter the key: ") 
            try: 
                val = int(input("Enter the value: ")) 
                insert_lst(size, key, val, hash_table) 
                print(f"Key '{key}' with value '{val}' inserted successfully.") 
                print("Hash Table:", hash_table) 
            except ValueError: 
                print("Invalid input! Value must be an integer.") 
        elif choice == 2: 
            key = input("Enter the key to delete: ") 
            print(delete_key(key, hash_table)) 
        elif choice == 3: 
            key = input("Enter the key to find: ") 
            print(find_key(key, hash_table)) 
        elif choice == 4: 
            print("Exiting program. Goodbye!") 
            break 
        else: 
            print("Invalid input! Please choose a number between 1 and 4.") 
 
main() 
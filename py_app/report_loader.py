import os
import pickle
import subprocess

def run_calc(expr):
    # CWE-95: опасное выполнение кода через eval
    return eval(expr)

def load_data(raw_bytes):
    # CWE-502: опасная десериализация через pickle
    return pickle.loads(raw_bytes)

def fetch_report(server_ip):
    # CWE-78: инъекция системных команд
    cmd = f"ping -c 1 {server_ip}"
    subprocess.run(cmd, shell=True)

def read_user_file(filename):
    # CWE-22: выход за пределы директории
    path = f"./reports/{filename}"
    with open(path, "r") as f:
        return f.read()

def process_items():
    items = [10, 20, 30]
    idx = int(input("Enter index (0-2): "))
    # CWE-129: выход за границы списка
    print(f"Item value: {items[idx]}")

def main():
    while True:
        print("\n=== Report Loader Utility ===")
        print("1. Run Math Evaluator")
        print("2. Ping Remote Server")
        print("3. Read Report File")
        print("4. Get Array Item")
        print("5. Load Pickle Data")
        print("6. Exit")
        
        cmd = input("Select option: ")

        if cmd == "1":
            txt = input("Enter math expression: ")
            res = run_calc(txt)
            print(f"Result: {res}")
        elif cmd == "2":
            ip = input("Enter server IP: ")
            fetch_report(ip)
        elif cmd == "3":
            fname = input("Enter filename: ")
            data = read_user_file(fname)
            print(f"Content:\n{data}")
        elif cmd == "4":
            process_items()
        elif cmd == "5":
            print("Loading raw test object...")
            # Передаём тестовый байтовый поток для вызова десериализации
            dummy = pickle.dumps({"status": "ok"})
            res = load_data(dummy)
            print(f"Loaded: {res}")
        elif cmd == "6":
            print("Bye!")
            break
        else:
            print("Invalid choice")

if __name__ == "__main__":
    main()
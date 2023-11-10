import os
import time

home_directory = os.path.expanduser( '~' )
chat_log_path = os.path.join(home_directory, "Documents", "Klei", "DoNotStarveTogether", "client_chat_log.txt")

def follow(thefile):
    thefile.seek(0,2)
    while True:
        line = thefile.readline()
        if not line:
            time.sleep(1)
            continue
        yield line

if __name__ == '__main__':
    chat_log = open(chat_log_path, "r")
    log_lines = follow(chat_log)
    for line in log_lines:
        print(line,)
        if "desligar" in line:
            print("desligando...")
            os.system('shutdown -s -t 60')
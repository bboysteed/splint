"""
    @requirement
        - python版本大于3.5
        - splint cppcheck有环境变量
    @用法
        python main.py test.c


"""
import csv
import re

import subprocess
import sys
try:
    agv = sys.argv[1]
except IndexError:
    print("\033[32m{}\033[0m".format("""
    error: 错误语法
    
    @requirement
        - python版本大于3.5
        - splint cppcheck有环境变量
    @用法
        python main.py test.c
    """))
    exit(1)
if __name__ == '__main__':
    process1 = subprocess.Popen(f"splint {agv}", stdout=subprocess.PIPE, shell=True)
    process1.wait()
    res = process1.stdout.read().decode()
    ans = re.findall(r'(.*?):(\d+):.*?:(.*?)\n', res)
    file = open("./result.csv", "w+")
    csv_writer = csv.writer(file)
    csv_writer.writerow(["index", "tool", "file name", "rows number", "reason"])
    b = [[str(ans.index(item)), "splint"] + [str(i).strip() for i in item] for item in ans]
    csv_writer.writerows(b)

    process2 = subprocess.Popen(f"cppcheck {agv}", stderr=subprocess.PIPE, shell=True)
    process2.wait()
    res = process2.stderr.read().decode()
    ans = re.findall(r'(.*?):(\d+):.*?:(.*?)\n', res)
    # csv_writer.writerow(["index", "tool", "file name", "rows number", "reason"])
    b = [[str(ans.index(item)), "cppcheck"] + [str(i).strip() for i in item] for item in ans]
    csv_writer.writerows(b)

    file.close()


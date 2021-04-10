# import csv
#
# a = [('division_by_zero_1.c', '18', 'error', 'Uninitialized variable: f [uninitvar]'), ('division_by_zero_1.c', '20', 'error', 'Uninitialized variable: c [uninitvar]'), ('division_by_zero_1.c', '50', 'error', 'Uninitialized variable: n2 [uninitvar]'), ('division_by_zero_1.c', '18', 'note', "Calling function 'div', 2nd argument 'f' value is <Uninit>"), ('division_by_zero_1.c', '50', 'note', 'Uninitialized variable: n2')]
# b = [[str(i) for i in item] for item in a]
# with open("./text.txt","w+") as f:
#     rter = csv.writer(f)
#     rter.writerows(b)
#     f.close()
import re

if __name__ == '__main__':

    s = """
    Checking division_by_zero_1.c ...
division_by_zero_1.c:18:19: error: Uninitialized variable: f [uninitvar]
        a = div(a,f);
                  ^
division_by_zero_1.c:20:12: error: Uninitialized variable: c [uninitvar]
        f+=c;
           ^
division_by_zero_1.c:50:15: error: Uninitialized variable: n2 [uninitvar]
    return n1/n2;
              ^
division_by_zero_1.c:18:19: note: Calling function 'div', 2nd argument 'f' value is <Uninit>
        a = div(a,f);
                  ^
division_by_zero_1.c:50:15: note: Uninitialized variable: n2
    return n1/n2;
    """
    ans = re.findall(r'(.*?):(\d+):.*?:(.*?)\n', s)
    print(ans)
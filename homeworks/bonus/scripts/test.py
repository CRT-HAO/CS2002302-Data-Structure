import random
import subprocess

program1_path = "/Users/hao/Downloads/hwbonus/build/hwbonus"
program2_path = "/Users/hao/GitHub/CS2002302-Data-Structure/homeworks/bonus/build/bonus"
# program2_path = "/Users/hao/Downloads/vup/build/vup"


def runProgram(path: str, data: str) -> str:
    process = subprocess.Popen(
        [path],
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
    )
    inputdata = bytes(data, "utf-8")
    stdoutdata, _ = process.communicate(input=inputdata)

    return stdoutdata.decode("utf-8")


def main():
    abc = [
        "a",
        "b",
        "c",
        "d",
        "e",
        "f",
        "g",
        "h",
        "i",
        "j",
        "k",
        "l",
        "m",
        "n",
        "o",
        "p",
        "q",
        "r",
        "s",
        "t",
        "u",
        "v",
        "w",
        "x",
        "y",
        "z",
    ]

    while True:
        data: str = ""

        v = random.randint(2, 26)
        e = random.randint(v, 100)
        # print("V={}, E={}".format(v, e))

        vars: set[str] = set()
        while len(vars) < v:
            var = random.choice(abc)
            if var not in vars:
                vars.add(var)

        print("{} {} {}".format(v, e, random.choice(list(vars))))
        data += "{} {} {}\n".format(v, e, random.choice(list(vars)))

        dijk = random.randint(0, 1) == 1

        for _ in range(e):
            src = random.choice(list(vars))
            vars_tmp = vars.copy()
            vars_tmp.remove(src)
            dest = random.choice(list(vars_tmp))
            weight = random.randint(1 if dijk else -5, 5)
            print("{} {} {}".format(src, dest, weight))
            data += "{} {} {}\n".format(src, dest, weight)

        # print(vars)

        print("Data: \n{}".format(data))

        ans1 = runProgram(program1_path, data)
        ans2 = runProgram(program2_path, data)

        print("Ans1: \n{}".format(ans1))
        print("Ans2: \n{}".format(ans2))

        if ans1 != ans2:
            print("Answer different!")
            break


if __name__ == "__main__":
    main()

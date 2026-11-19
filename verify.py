"""Compile and check all 15 homework programs with GCC and G++."""
from pathlib import Path
import os
import re
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parent
SOURCES = sorted([*ROOT.glob("*/*.c"), *ROOT.glob("*/*.cpp")])
EXAMPLES = {}


def run(executable, entry=""):
    return subprocess.run(
        [str(executable)], input=entry + "\n", text=True, encoding="utf-8",
        capture_output=True, timeout=5, check=False,
    )


def verify():
    assert len(SOURCES) == 15
    with tempfile.TemporaryDirectory(prefix="codex-hw4-build-") as work:
        work = Path(work)
        executables = {}
        for source in SOURCES:
            compiler = "g++" if source.suffix == ".cpp" else "gcc"
            standard = "-std=c++17" if source.suffix == ".cpp" else "-std=c17"
            executable = work / (source.stem + ".exe")
            subprocess.run(
                [compiler, standard, "-Wall", "-Wextra", "-Wconversion", "-Werror",
                 "-pedantic", source.name, "-o", str(executable)],
                cwd=source.parent, check=True,
            )
            executables[source.stem] = executable

        for name, executable in executables.items():
            entry = {"P19": "Hello there", "P37": "36"}.get(name, "")
            result = run(executable, entry)
            assert result.returncode == 0, (name, result.stderr)
            EXAMPLES[name] = {"input": entry, "stdout": result.stdout, "stderr": result.stderr}

        for name, values in (
            ("P04", [0] * 10),
            ("P05", [32, 27, 64, 18, 95, 14, 90, 70, 60, 37]),
            ("P06", list(range(2, 21, 2))),
        ):
            rows = [list(map(int, line.split())) for line in EXAMPLES[name]["stdout"].splitlines()[1:]]
            assert rows == [[i, value] for i, value in enumerate(values)], (name, rows)
        assert EXAMPLES["P07"]["stdout"].strip() == "陣列元素總和為 383"
        for i, (line, value) in enumerate(zip(EXAMPLES["P08"]["stdout"].splitlines()[1:],
                                            [19, 3, 15, 7, 11, 9, 13, 5, 17, 1])):
            index, actual, stars = line.split()
            assert (int(index), int(actual), stars) == (i, value, "*" * value)
        assert EXAMPLES["P13"]["stdout"] == (
            "陣列 1 的各列\n1 2 3\n4 5 6\n"
            "陣列 2 的各列\n1 2 3\n4 5 0\n陣列 3 的各列\n1 2 0\n4 0 0\n"
        )
        output = EXAMPLES["P14"]["stdout"]
        for text in ("最低成績：68", "最高成績：96", "學生 0 的平均成績：76.00",
                     "學生 1 的平均成績：87.50", "學生 2 的平均成績：81.75"):
            assert text in output, text
        assert EXAMPLES["P19"]["stdout"] == (
            "第一個字串：Hello\n第二個字串：string literal\n逐字元輸出：H e l l o\n"
        )
        for entry in ("", "a" * 20):
            assert run(executables["P19"], entry).returncode == 1
        assert run(executables["P19"], "a" * 19).returncode == 0
        for name in ("P19", "P37"):
            assert "請輸入" in EXAMPLES[name]["stderr"]
        static = re.findall(r"array1\[\d\] = (\d+)", EXAMPLES["P21"]["stdout"])
        automatic = re.findall(r"array2\[\d\] = (\d+)", EXAMPLES["P21"]["stdout"])
        assert static == list(map(str, [0, 0, 0, 5, 5, 5, 5, 5, 5, 10, 10, 10]))
        assert automatic == list(map(str, [1, 2, 3, 6, 7, 8] * 2))
        assert EXAMPLES["P25"]["stdout"] == "呼叫前 x = 100\nxref = 101\n呼叫後 x = 101\n回傳值 y = 101\n"
        addresses = [line.split(" = ")[1] for line in EXAMPLES["P26"]["stdout"].splitlines()[:3]]
        assert len(set(addresses)) == 1 and int(addresses[0], 16) != 0
        assert EXAMPLES["P28"]["stdout"] == (
            "傳遞陣列前\n0 1 2 3 4\n傳遞陣列後\n0 2 4 6 8\n"
            "傳遞單一元素前 a[3] = 6\n函式內的副本為 12\n傳遞單一元素後 a[3] = 6\n"
        )
        assert EXAMPLES["P30"]["stdout"] == "反轉前：3 5 7\n反轉後：7 5 3\n"
        for entry, expected in (("0", "陣列索引為 0"), ("198", "陣列索引為 99"),
                                ("36", "陣列索引為 18"), ("37", "找不到"), ("-2", "找不到")):
            result = run(executables["P37"], entry)
            assert result.returncode == 0 and expected in result.stdout
        for entry in ("", "abc", "36abc", "2147483648", "9" * 100):
            assert run(executables["P37"], entry).returncode == 1
        assert EXAMPLES["6.11"]["stdout"] == (
            "排序前\n2 6 4 8 10 12 89 68 45 37\n排序後\n2 4 6 8 10 12 37 45 68 89\n"
        )

        # Count comparisons in the original sort loop to verify both optimizations.
        sorting = (ROOT / "6.11/6.11.c").read_text(encoding="utf-8-sig")
        sorting = sorting.replace('#include "../console.h"', '#include "console.h"')
        sorting = sorting.replace("void bubbleSort", "static int comparisons;\nvoid bubbleSort")
        sorting = sorting.replace("array[i] > array[i + 1]", "++comparisons, array[i] > array[i + 1]")
        sorting = sorting.replace("int main(void)", "int example_main(void)")
        harness = work / "sort_check.c"
        harness.write_text(sorting + """
#include <assert.h>
int main(void)
{
    int reverse[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    bubbleSort(reverse, 10);
    assert(comparisons == 45);
    for (int i = 0; i < 10; ++i) assert(reverse[i] == i);
    comparisons = 0;
    bubbleSort(reverse, 10);
    assert(comparisons == 9);
    int duplicates[] = {3, -1, 3, 0, -1};
    bubbleSort(duplicates, 5);
    for (int i = 1; i < 5; ++i) assert(duplicates[i - 1] <= duplicates[i]);
    comparisons = 0;
    bubbleSort(duplicates, 0);
    bubbleSort(duplicates, 1);
    assert(comparisons == 0);
    return 0;
}
""", encoding="utf-8")
        (work / "console.h").write_bytes((ROOT / "console.h").read_bytes())
        checker = work / "sort_check.exe"
        subprocess.run(["gcc", "-std=c17", "-Wall", "-Wextra", "-Werror",
                        str(harness), "-o", str(checker)], check=True)
        subprocess.run([str(checker)], check=True, timeout=5)

        for source in SOURCES:
            target = source.with_suffix(".exe")
            # Copy before replacing so the build can be on a different drive.
            candidate = source.parent / (source.stem + ".new.exe")
            try:
                candidate.write_bytes(executables[source.stem].read_bytes())
                os.replace(candidate, target)
            finally:
                if candidate.exists():
                    candidate.unlink()
    print("All 15 builds and behavior checks passed, including both bubble-sort optimizations.")


if __name__ == "__main__":
    verify()

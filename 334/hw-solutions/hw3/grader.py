import glob
import os
from pathlib import Path
import sys
from typing import Type



EXE_NAME = "hw3"


def shell_capture(command, force_type: Type = str):
    out = os.popen(command).read()
    return force_type(out.strip())


def grade(image_file: str, input_dir: str, output_dir: str):
    input_dir = Path(input_dir)
    output_dir = Path(output_dir)
    new_output_dir = output_dir.parent / "outputs2"
    new_output_dir.mkdir(parents=True, exist_ok=True)

    for in_file in input_dir.iterdir():
        if in_file.is_dir():
            continue
        out_file = new_output_dir / in_file.name.replace("input", "output")
        os.system(f"./{EXE_NAME} {image_file} < {in_file} > {out_file}")

    n_test_cases = shell_capture(f"ls -l {input_dir.as_posix()} | wc -l", int) - 1
    n_diff = shell_capture(f"diff -q {output_dir.as_posix()} {new_output_dir.as_posix()}| wc -l", int) - 1
    print("# of test cases:", n_test_cases)
    print("# of different outputs:", n_diff)
    print("Miss rate:", n_diff/n_test_cases)
    print("Grade:", 100*(1-(n_diff/n_test_cases)))

if __name__ == "__main__":
    args = sys.argv[1:]
    grade(*args)

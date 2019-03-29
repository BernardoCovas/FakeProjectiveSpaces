def newCFile(N, K, func):
    return f"""\
int libinfo_N = {N};
int libinfo_K = {K};

int determinantQ(int *x)
{{
    return {func};
}}

"""

if __name__ == "__main__":
    import argparse
    import os

    parser = argparse.ArgumentParser()
    parser.add_argument("file", type=str, help="File with the simplefied functions. Output of matlab.")
    parser.add_argument("folder", type=str, help="Folder in which the C files will be placed.")

    args = parser.parse_args()

    i = 0
    with open(args.file) as f:
        for line in f:
            if (len(line) < 10):
                continue

            i += 1
            line = line.replace("\n", "")
            with open(os.path.join(args.folder, f"{i:02d}.c"), "w") as cf:
                cf.write(newCFile(13, 48, line))
def mycsvread(csvfile, code):
    ans = []
    with open(csvfile, "r", encoding=code) as f:
        for line in f:
            ans.append(line.rstrip("\n").split(","))
    return ans
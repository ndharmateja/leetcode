nums = [1, 2, 3, 4]
n = len(nums)
count1 = 0
count2 = 0


def dfs1(sequence, start_index):
    global count1
    count1 += 1
    print(sequence)
    for i in range(start_index, n):
        sequence.append(nums[i])
        dfs1(sequence, i + 1)
        sequence.pop()


def dfs2(sequence, i):
    global count2
    count2 += 1
    if i == n:
        print(sequence)
        return

    sequence.append(nums[i])
    dfs2(sequence, i + 1)
    sequence.pop()

    dfs2(sequence, i + 1)


dfs1([], 0)
print(f"dfs1 count: {count1}")
dfs2([], 0)
print(f"dfs2 count: {count2}")

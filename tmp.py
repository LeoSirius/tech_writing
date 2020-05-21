

def csv_reader(file_name):
    # file = open(file_name)           # open return lazy obj
    # result = file.read().split("\n") # 这里会加载所有数据到内存，可能会报MemoryError
    # return result

    for row in open(file_name, "r"):
        yield row

csv_gen = csv_reader("test_csv.csv")
row_count = 0

for row in csv_gen:
    row_count += 1

print(f"Row count is {row_count}")
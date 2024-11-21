### 某行是否包括

```python
import pandas as pd
import os

# 假设BASE_DIR是您存放Excel文件的目录
BASE_DIR = 'F:\\1school\\校团委文案编辑\\2024.11.19网络安全文化节'  # 请确保这里的路径是正确的

# 读取整个Excel文件
excel_file = '2024网络安全文化节评分计算.xlsx'  # Excel文件名
xls = pd.ExcelFile(os.path.join(BASE_DIR, excel_file))

# 要搜索的字符串
search_string = '法学院'  # 替换为您想要搜索的字符串

# 初始化奖项统计字典
awards_count = {'一等奖': 0, '二等奖': 0, '三等奖': 0, 'NaN': 0}

# 遍历每个sheet并进行处理
for sheet_name in xls.sheet_names:
    df = pd.read_excel(xls, sheet_name=sheet_name)
    print(f"Data from sheet '{sheet_name}' containing '{search_string}' and non-NaN in column 8:")
    # 使用df.apply函数检查每一行，如果包含搜索字符串，并且第八列不是NaN，则返回该行
    filtered_rows = df.apply(lambda row: (row.astype(str).str.contains(search_string, na=False).any() and
                                          pd.notna(row.iloc[7])), axis=1)
    # 输出包含搜索字符串的行，不打印表头和索引
    if not df[filtered_rows].empty:
        print(df[filtered_rows].to_string(index=False, header=False))

    # 统计奖项
    for index, row in df[filtered_rows].iterrows():
        if pd.notna(row.iloc[7]):
            award = row.iloc[7]
            if award in awards_count:
                awards_count[award] += 1
            else:
                awards_count['其他'] += 1  # 如果有不属于前三者的奖项，计入其他

# 打印统计结果
print("Awards count:")
for award, count in awards_count.items():
    print(f"{award}: {count}")
```

### 每行的某一格是否包括

```python
import pandas as pd
import os

# 假设BASE_DIR是您存放Excel文件的目录
BASE_DIR = 'F:\\1school\\校团委文案编辑\\2024.11.19网络安全文化节'  # 请确保这里的路径是正确的

# 读取整个Excel文件
excel_file = '2024网络安全文化节评分计算.xlsx'  # Excel文件名
xls = pd.ExcelFile(os.path.join(BASE_DIR, excel_file))

# 要搜索的字符串
strings=['建筑','机械','能源','信息','土木','电子','数学','自动化','计软智','物理']
search_string = '建筑'  # 替换为您想要搜索的字符串

# 初始化奖项统计字典
awards_count = {'一等奖': 0, '二等奖': 0, '三等奖': 0, 'NaN': 0}
for search_string in strings:
    print('--------------------------\n',search_string)
    awards_count['一等奖']=0
    awards_count['二等奖']=0
    awards_count['三等奖']=0
    # 遍历每个sheet并进行处理
    for sheet_name in xls.sheet_names:
        df = pd.read_excel(xls, sheet_name=sheet_name)
        #print(f"Data from sheet '{sheet_name}' containing '{search_string}' and non-NaN in column 8:")
        # 使用df.apply函数检查每一行，如果包含搜索字符串，并且第八列不是NaN，则返回该行

        filtered_rows = df.apply(lambda row: ((search_string in row.iloc[2]) and
                                              pd.notna(row.iloc[7])), axis=1)
        # 输出包含搜索字符串的行，不打印表头和索引
        #if not df[filtered_rows].empty:
            #   print(df[filtered_rows].to_string(index=False, header=False))

        # 统计奖项
        for index, row in df[filtered_rows].iterrows():
            if pd.notna(row.iloc[7]):
                award = row.iloc[7]
                if award in awards_count:
                    awards_count[award] += 1
                else:
                    awards_count['其他'] += 1  # 如果有不属于前三者的奖项，计入其他

    # 打印统计结果
    print("Awards count:")
    for award, count in awards_count.items():
        print(f"{award}: {count}")
```


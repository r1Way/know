def find_invalid_utf8(filename):
    with open(filename, 'rb') as f:
        content = f.read()
    try:
        content.decode('utf-8')
        print("File is valid UTF-8")
    except UnicodeDecodeError as e:
        print(f"Invalid UTF-8 at byte {e.start}: {e.reason}")

find_invalid_utf8('SUMMARY.md')

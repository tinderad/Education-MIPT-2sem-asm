with open("Raw/400k-words.txt", "r") as txt:
    lines = list(txt)
    csv = open("Csv/400k-words.csv", "w")
    
    for line in lines:
        key = line.strip()
        csv.write(key +"=0\n")
    
    csv.close()

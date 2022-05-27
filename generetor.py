from fileinput import filename
import requests

word_site = "https://www.mit.edu/~ecprice/wordlist.10000"

response = requests.get(word_site)
WORDS = response.content.splitlines()
size = input()
for i in range(int(size)):
    print(WORDS[i].decode('utf-8'))
    

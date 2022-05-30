from fileinput import filename
import requests
from scipy import rand

word_site = "https://www.mit.edu/~ecprice/wordlist.10000"

response = requests.get(word_site)
WORDS = response.content.splitlines()
size = input()
for i in range(100,100 + int(size)):
    print(WORDS[i].decode('utf-8'))
    

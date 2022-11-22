import requests
from bs4 import BeautifulSoup
import re
import time

def main():
    start_time = time.time()

    URL = "https://learnjapanesedaily.com/most-common-japanese-words.html/"
    char_to_replace = {'<p>' : "", '</p>' : "", '<br/>' : ""}
    output = []
    count = 1

    romaji = input("Enter romaji: ")
    romaji = "(" + romaji + ")"
    
    while (count < 17): 
        page = requests.get(URL + str(count))
        soup = BeautifulSoup(page.content, "html.parser")
        results = soup.find(id="content")
        job_elements = results.find_all("p")
        for job_element in job_elements:
            output.append(str(job_element))
        count+=1

    for words in output:
        checker_flag = re.search("^<p>([1-9]|[1-9][0-9]|[1-9][0-9][0-9]). ", words)
        if checker_flag:
            for key, value in char_to_replace.items():
                words = words.replace(key, value)
                if romaji in words and "</p>" not in words:
                    print(words)
                    break
                    

    print("--- %s seconds ---" % (time.time() - start_time))
        

if __name__ == "__main__":
    main()
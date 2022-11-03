import requests
from bs4 import BeautifulSoup
import re
import time

start_time = time.time()

URL = "https://learnjapanesedaily.com/most-common-japanese-words.html/"
count = 1

char_to_replace = {'<p>' : "", '</p>' : "", '<br/>' : ""}

while (count < 17): 
    page = requests.get(URL + str(count))
    soup = BeautifulSoup(page.content, "html.parser")
    output = []
    results = soup.find(id="content")
    job_elements = results.find_all("p")
    for job_element in job_elements:
        output.append(str(job_element))

    if (count == 1):
        with open('common_words.txt', 'w') as f:
            for x in output:
                checker_flag = re.search("^<p>([1-9]|[1-9][0-9]|[1-9][0-9][0-9]). ", x)
                if checker_flag:
                    for key, value in char_to_replace.items():
                        x = x.replace(key, value)
                    f.write(x + "\n")
    else:
        with open('common_words.txt', 'a') as f:
            for x in output:
                checker_flag = re.search("^<p>([1-9]|[1-9][0-9]|[1-9][0-9][0-9]). ", x)
                if checker_flag:
                    for key, value in char_to_replace.items():
                        x = x.replace(key, value)
                    f.write(x + "\n")
    count += 1

# print(u'\u4E17\u754c\u3053\u3093\u3093\u3061\u306F')
# unicode_string = 'U+3044'
# print(unicode_string)
print("--- %s seconds ---" % (time.time() - start_time))

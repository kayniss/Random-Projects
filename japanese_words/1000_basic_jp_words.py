import requests
from bs4 import BeautifulSoup
import re
import time

def main():
    start_time = time.time()

    URL = "https://en.wiktionary.org/wiki/Appendix:1000_Japanese_basic_words"
    page = requests.get(URL)

    soup = BeautifulSoup(page.content, "html.parser")

    words = []

    table = soup.find('div', attrs = {'class':'mw-parser-output'}) 

    for row in table.findAll('li'):
        words.append(str(row)[str(row).find("title=")+len("title="):str(row).rfind("</li>")])

    count = 0
    for x in words:
        if (x[0] == '"'):
            break
        count += 1

    words = words[count:]
    for i in range(len(words)):
        print(words[i])
        # words[i] = words[i].split(">")[0]

    # for x in words:
    #     print(x)

    # data = soup.find("ul")

    # for li in data.find_all("li"):
    #     print(li.text, end=" ")

    # soup = list.find_all("div", class_="mw-parser-output")
    # print(soup)
    # soup = list.find_all("ul", class_="Jpan")
    # print(soup)

    # print(results)
    # print(type(results))

    # for word in words:
    #     print(word)

    # while (count < 17): 
    #     page = requests.get(URL + str(count))
    #     soup = BeautifulSoup(page.content, "html.parser")
    #     output = []
    #     results = soup.find(id="content")
    #     job_elements = results.find_all("p")
    #     for job_element in job_elements:
    #         output.append(str(job_element))

    #     if (count == 1):
    #         with open('common_words.txt', 'w') as f:
    #             for x in output:
    #                 checker_flag = re.search("^<p>([1-9]|[1-9][0-9]|[1-9][0-9][0-9]). ", x)
    #                 if checker_flag:
    #                     for key, value in char_to_replace.items():
    #                         x = x.replace(key, value)
    #                     f.write(x + "\n")
    #     else:
    #         with open('common_words.txt', 'a') as f:
    #             for x in output:
    #                 checker_flag = re.search("^<p>([1-9]|[1-9][0-9]|[1-9][0-9][0-9]). ", x)
    #                 if checker_flag:
    #                     for key, value in char_to_replace.items():
    #                         x = x.replace(key, value)
    #                     f.write(x + "\n")
    #     count += 1

    # print(u'\u4E17\u754c\u3053\u3093\u3093\u3061\u306F')
    # unicode_string = 'U+3044'
    # print(unicode_string)
    print("--- %s seconds ---" % (time.time() - start_time))

if __name__ == "__main__":
    main()
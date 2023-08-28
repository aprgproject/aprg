import logging
import os
import re
import sys
from tabulate import tabulate

logging.basicConfig(
    level=logging.INFO,
    format='[%(levelname)s] | \033[35m%(asctime)s\033[0m  | '
           '\033[33m%(filename)s:%(lineno)d\033[0m | %(message)s'
)

analyzer_issues_path = os.path.realpath(sys.argv[1])
logging.info("analyzer_issues_path: [%s]", analyzer_issues_path)

logging.info("Counting all issues based from analyzer output...")

issue_to_count_map = {}
with open(analyzer_issues_path, 'r', encoding='utf-8') as file:
    for line in file:
        PATTERN = r'\[(.*?)\]'
        matches = re.findall(PATTERN, line.strip())
        if matches:
            for issues_list in matches:
                issues = issues_list.split(',')
                for issue in issues:
                    issue_to_count_map[issue] = issue_to_count_map.get(
                        issue, 0) + 1

logging.info("Counting finished, generating report...")

# Sort the issue_to_count_map based on counts in descending order
sorted_list = sorted(issue_to_count_map.items(),
                     key=lambda item: item[1], reverse=True)
issue_to_count_map = dict(sorted_list)

print("\n")
logging.info("Printing the data:")
logging.info("issue_to_count_map: [%s]", issue_to_count_map)

for issue, count in issue_to_count_map.items():
    logging.info("issue: [%s] | number of hits: %d", issue, count)

# Generating table
print("\n")
logging.info("Printing the data in table:")
table_data = [[issue, count] for issue, count in issue_to_count_map.items()]
headers = ["Issue", "Number Of Hits"]
table = tabulate(table_data, headers=headers, tablefmt="grid")
print(table)

# Extract issue names and counts for plotting
print("\n")
logging.info("Printing the data in bar graph:")
LONGEST_BAR = 100
max_count = max(issue_to_count_map.values())
for issue, count in issue_to_count_map.items():
    display_bar_length = int(LONGEST_BAR * (count / max_count))
    display_bar = "X" * display_bar_length
    print(f"{issue:<60}: [{display_bar:<{LONGEST_BAR}}] ({count} hits)")

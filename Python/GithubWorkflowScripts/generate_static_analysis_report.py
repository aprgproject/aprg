import logging
import os
import re
import sys


logging.basicConfig(
    level=logging.INFO,
    format='[%(levelname)s] | \033[35m%(asctime)s\033[0m  | '
           '\033[33m%(filename)s:%(lineno)d\033[0m | %(message)s'
)


def find_files(directory, filename):
    found_files = []
    for root, _, files in os.walk(directory):
        if filename in files:
            found_files.append(os.path.join(root, filename))
    return found_files


REPORT_FILENAME = sys.argv[1]
SCRIPT_DIRECTORY = __file__
logging.info("Generate Static Analysis Report Script")
logging.info("The script_directory is [%s]", SCRIPT_DIRECTORY)
aprg_directory = os.path.abspath(os.path.join(SCRIPT_DIRECTORY, "../../.."))
logging.info("The aprg_directory is [%s]", aprg_directory)

logging.info("Searching all issues based from different analyzer files...")

reports = find_files(aprg_directory, REPORT_FILENAME)
if not reports:
    logging.info("The filename [%s] is not found", REPORT_FILENAME)
    sys.exit(1)

issue_to_count_map = {}
for report_file_path in reports:
    logging.info("Found report_file_path: [%s]", report_file_path)
    with open(report_file_path, 'r', encoding='utf-8') as file:
        for line in file:
            PATTERN = r'\[(.*?)\]'
            matches = re.findall(PATTERN, line.strip())
            if matches:
                for issues_list in matches:
                    issues = issues_list.split(',')
                    for issue in issues:
                        issue_to_count_map[issue] = issue_to_count_map.get(
                            issue, 0) + 1

logging.info("Search finished, generating report...")

# Sort the issue_to_count_map based on counts in descending order
sorted_list = sorted(issue_to_count_map.items(),
                     key=lambda item: item[1], reverse=True)
issue_to_count_map = dict(sorted_list)

print("\n")
logging.info("Printing the data:")
logging.info("issue_to_count_map: [%s]", issue_to_count_map)

for issue, count in issue_to_count_map.items():
    logging.info("issue: [%s] | number of hits: %d", issue, count)

# Extract issue names and counts for plotting
print("\n")
logging.info("Printing the data in a bar graph:")
MIN_BAR_LENGTH = 1
MAX_BAR_LENGTH = 59
BAR_TO_SCALE = MAX_BAR_LENGTH-MIN_BAR_LENGTH
max_count = max(issue_to_count_map.values())
with open('StaticAnalysisOverallReport.txt', 'w') as overall_report_file:
    overall_report_file.write('Static Analysis overall report:\n')
    for issue, count in issue_to_count_map.items():
        display_bar_length = int(
            BAR_TO_SCALE * (count / max_count)) + MIN_BAR_LENGTH
        display_bar = "X" * display_bar_length
        overall_report_line = f"{issue:<60}: [{display_bar:<{MAX_BAR_LENGTH}}] ({count} hits)"
        print(overall_report_line)
        overall_report_file.write(overall_report_line + "\n")

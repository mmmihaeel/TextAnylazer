# Text Analyzer

Text Analyzer is a C++ application designed to perform various text analysis operations such as counting letters, digits, words, brackets, punctuation marks, special symbols, and whitespace characters. The program also supports file-based input and output, ensuring efficient and accurate processing of text data.

## Features

- **Bracket Counter**: Counts round, square, and curly brackets in the text.
- **Digit Counter**: Counts numeric digits.
- **Letter Counter**: Counts alphabetic letters, with an option for case insensitivity.
- **Punctuation Counter**: Counts common punctuation marks like `.`, `,`, `;`, etc.
- **Special Symbol Counter**: Counts special symbols like `@`, `#`, `$`, etc.
- **Whitespace Counter**: Counts whitespace characters.
- **Word Counter**: Counts words while ignoring specified stopwords.

## Project Structure

The program is modular and adheres to object-oriented programming principles. Key components include:

- **Model-View-Controller Architecture**:
  - **Model**: `TextAnylazerModel` manages results and notifies observers.
  - **View**: `TextAnylazerView` handles displaying results.
  - **Controller**: `TextAnylazerController` orchestrates the analysis process.

- **Operation Classes**:
  - Implement operations like counting brackets, digits, letters, punctuation, special symbols, whitespace, and words.
  - Each class validates input and computes its respective analysis.

- **Error Handling**:
  - Uses `ValidationException` for clear error reporting on invalid input.

- **Observer Pattern**:
  - Dynamically updates observers when new results are available.

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/text-analyzer.git
   cd text-analyzer
   ```
2. Build the project:

```bash
mkdir build
cd build
cmake ..
make
  ```
3. Run the program:
```bash
./TextAnalyzer
  ```

## Usage
Prepare an input .txt file containing the text to analyze.
Run the program and specify the input and output file names:
```bash
Enter input file name: input.txt
Enter output file name: output.txt
   ```
The program processes the text and saves the results to the specified output file.
Example Output
------------------------------------------
          Text Analysis Results           
------------------------------------------
| Round Brackets: 10                     |
| Square Brackets: 5                     |
| Curly Brackets: 8                      |
| Digits: 15                             |
| Letters: 120                           |
| Punctuation Marks: 30                  |
| Special Symbols: 7                     |
| Whitespace Characters: 40              |
| Word Count: 50                         |
------------------------------------------
## [END OF RESULTS]
## Contributing
Contributions are welcome! Feel free to submit issues or pull requests to improve the project.

## License
This project is licensed under the MIT License.

## Acknowledgments
Inspired by the need for robust and flexible text analysis tools.
Developed using modern C++ features and best practices.

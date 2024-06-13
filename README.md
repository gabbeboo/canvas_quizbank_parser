
# Quiz-parser 


## How to use the quiz-parser

- Clone the repository
- "cd" into the repository
- "python3 quiz_parser.py <input_file.md>"
- Install the required packages if you don't have them already
- Outut will be a zip file with the same name as the input file
- Go to Canvas and import the zip file as QTI-zipfil.



## What should the quiz-bank markdown file look like?

- The file should be a markdown file with the extension .md
- The file should contain questions and alternatives in the following format:
- Title of the question should be in the format "# Course : Theme " for example "# Java : Variables", 
  there should only be one header 1 in the file.

- The question should be in the format "## Question number" for example "## Question 1"
  Note: It is not required to have the question number in the question, but it is recommended
  it can have any text as long as it is a header 2. The question title in the quizbank will regardless be
  the text after the ':' in the header 1.


- The answer to the questions should be in the format "- [ ] alternative" for example "- [ ] 5"
  The correct answer should be marked with an 'x' for example "- [x] 7"
  If there are multiple correct answers, they should all be marked with an 'x', this will automatically
  make the question a multiple choice question in the quizbank. Wrong answers are left unmarked.

- Example file : 
```markdown
    # Java : Variables
    
    ## Question 1
    What is the value of the variable b?
    ```
    int a = 5;
    int b = a;
    int a = 0;
    ```
    - [x] 5
    - [ ] 10
    - [ ] 7
    - [ ] Undefined
```markdown

# Generating questions with LLM(ChatGPT)
- This program works well with auto generating questions
  From a larger language model like GPT-3 or GPT-4

  However the triple backticks ```makes chat render its own code and makes it hard to copy. Therefore prompt it with "Escape all the backticks in the markdown file" and it should now be all in a single code block, ready to be copied. Remove these escape characters before running the quiz-parser(I recommend just Ctrl+F and replace all of them with nothing).

  Working with GitHub Co-pilot in your editor is also a good idea, as it can help you generate the questions and alternatives.


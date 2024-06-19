# תכנות מערכות 2 - מטלה 4
 
4 ספרות אחרונות של ת"ז: 1536

מייל: yairjacob620@gmail.com

מימוש של עץ גנרי בהתאם להנחיות המטלה.

## אופן המימוש והחלוקה בקוד
קודקוד בעץ ממומש בתור המחלקה `Node` (שמכילה, בין היתר, משתנה גנרי), העץ עצמו בתור המחלקה `Tree` (שמכילה, בין היתר, שורש מסוג `Node`) והאיטרטור ל-`Tree` ממומש בתור המחלקה הפנימית `Treeterator`. ה-GUI מומש דרך `Qt Creator` בעזרת המחלקה `TreeVisualizer` (שיורשת ממחלקות בספריות של Qt). 
## אופן הפעלת התוכנית
| Command | Description |
| ---------- | ---------- |
| `make` or <br>`make tree` | Creates and runs an executable `main` which builds a binary int tree, iterate over it with the different iterators and displays it in a GUI (if run through Qt Creator). |
| `make main` | Creates an executable called `main` (without running it). *|
| `make test` | Creates and runs a doctest executable called `tests` that runs dozens of tests on the program. Prints a summary of the tests. |
| `make clean` | Deletes all .o files and executables. |

* Main can be executed without any arguments, for the same outputs as `make tree`, and can also be executed with the following arguments:
* "2" - Creates and iterates over a random 30-ary long-tree, and displays it in a GUI (if run through Qt Creator).
* "3" - Creates and iterates over a random 30-ary Complex-tree, and displays it in a GUI (if run through Qt Creator).

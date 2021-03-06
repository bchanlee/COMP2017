# Assignment 1 - Handling Files and Strings

Program finds the next earliest train departure after arrival at a station.

### Standard Input
* Timetable data is supplied via standard input
* Each entry is `<source>::<destination>::<time>`
* `<time>` is in 24-hour format `<hh>:<mm>:<ss>`
* Each entry should have a maximum 4096 characters

### Command Line Arguments
* The station that is arrived at is passed via command line arguments
* `./timetable <source> <destination> <time>`

### Output
* Standard output
* `The next train to <destination> from <source> departs at <time>`

### Compilation
* `make timetable` to compile program
* `gcc-10` for macOS

### Tests
* Examples are seen in `tests` folder
* `testinfo.txt` has information about all the tests
* `make test` to run tests

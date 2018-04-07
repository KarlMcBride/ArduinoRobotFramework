Project purpose:

For testing applications, Robot Framework may be used to provide a way of automating test runs, reducing the reliance of manual testing, and ensuring that local changes in the code base do not have detrimental effect on existing behaviour elsewhere.

Robot Framework be used to simulate physical interactions (magnetic card swipes and UI input via test harnesses), but not EMV inserts. As the EMV kernel is a blackbox OS operation, we cannot send API calls to simulate inserts. A mock kernel was previously implemented to allow this, however it did not perform identically to the real kernel.

As such, this project was created to allow our Robot Framework based testing to drive an Arduino board, and automate physical actions.

A day one example of this in operation can be found here: https://photos.app.goo.gl/ivUzSO6lLDB9AfV12
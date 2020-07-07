# TrayIconQtProject

This project create a sample app (created via framework QT 5.9.6) with a basic GUI and a class to handle Tasks.
The main will simply start the window, while actions and magic will run in classes instance of mainwindow and the object task.

In mainwindow it's initialized an wasy GUI with few elements necessary to interact and let the task run, or take an input (needed fo task one). Also, A systemTrayIcon will be
initialized, allowing the app to run in background and managing the window GUI via a simple menu attached to the trayIcon.

The task class will manage the real work, there are configured slots to handle the two type of task configured. Timing and queues are handled via Qtimer class.

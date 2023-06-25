const electron = require("electron");
const path = require("path");
const childProcess = require('child_process');

const app = electron.app;
const BrowserWindow = electron.BrowserWindow;

let mainWindow;

function createWindow() {
    // Create the browser window.
    mainWindow = new BrowserWindow({
        width: 1400,
        height: 1000,
        webPreferences: { nodeIntegration: true, contextIsolation: false },
    });
    // and load the index.html of the app.
    mainWindow.loadFile(path.join(__dirname, "./build/index.html"));

    // Start the Node.js server as a child process
    const serverProcess = childProcess.spawn('npm', ['run', 'local'], {
        cwd: path.join(__dirname, '..', 'backend'), // The folder to execute the command in

    });

    serverProcess.stdout.on('data', (data) => {
        console.log(`Server output: ${data}`);
    });

    // setting react console to electron console
    mainWindow.webContents.on('console-message', (event, level, message, line, sourceId) => {
        console.log(message);
    }
    );

}

app.whenReady().then(() => {
    createWindow();

    app.on('activate', function () {
        if (BrowserWindow.getAllWindows().length === 0) createWindow();
    });
});

app.on('window-all-closed', function () {
    if (process.platform !== 'darwin') app.quit();
});
import time
import win32gui
import urllib.request

PERIOD = 3  # seconds

def main():
    # Check for window existence every `PERIOD` seconds
    # If the window shows up turn on the light by executing a
    # GET request at http://onair.iot/on
    # If the window disappears turn off the light by executing a
    # GET request at http://onair.iot/off

    try:
        urllib.request.urlopen("http://onair.iot/off", timeout=1).read()
    except urllib.error.URLError as e:
        print(f"Error: {e}")

    window_handle = None
    while True:
        time.sleep(PERIOD)

        try:
            if not window_handle:
                window_handle = win32gui.FindWindow(None, "Zoom meeting") or win32gui.FindWindow(None, "Zoom Meeting 40-Minutes ")
                if window_handle:
                    print("Turning on the light")
                    urllib.request.urlopen("http://onair.iot/on", timeout=1).read()
            else:
                if not win32gui.IsWindow(window_handle):
                    window_handle = None
                    print("Turning off the light")
                    urllib.request.urlopen("http://onair.iot/off", timeout=1).read()
        except urllib.error.URLError as e:
            print(f"Error: {e}")

if __name__ == '__main__':
    main()

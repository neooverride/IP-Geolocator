# 📍 IP-Geolocator 🌍

![Alt Text](https://github.com/NeoOverride/IP-Geolocator/blob/main/image.png)

- This script fetches geolocation information about an IP address using APIs. It provides details such as the country, city, region, timezone, and more. The input/output is displayed in a visually appealing bright bold white color for better readability.

## 🚀 Features 
1. Fetches public IP address automatically.
2. Provides geolocation details of any IP address.
3. Bright bold white formatting for input/output.
4. Error handling for invalid inputs.
5. Typewriter animation for a smooth output experience.
6. Displays Google Maps link for the geolocation.

## ⚙️📦 Required Dependencies:
- Install the cURL library:
```bash
sudo apt-get install libcurl4-openssl-dev
```
- Install the nlohmann/json library:
```bash
sudo apt-get install nlohmann-json3-dev
```
## 🛠️ Installation:
- Clone the repository to your local machine:
```bash
https://github.com/lainwiredcomputer/IP-Geolocator.git
```
- Navigate into the project directory:
```bash
cd IP-Geolocator
```
## 🛡️ Compilation Instructions:
```bash
g++ ipGeolocator.cpp asciiArt.cpp -o outputfile -lcurl
```
- Run the compiled binary:
```bash
./outputfile
```
## 🖼️ Expected Output:
- When prompted:
```bash
Do you want to use your public IP address (y/n)?
```
- If you enter Y/y then it fetches IP geolocation of your router's IP.
- When I entered Google's public DNS IP in the given image, this information was displayed.

![Alt Text](https://github.com/x4ldr1t89z/IP-Geolocator/blob/main/image_.png)

## APIs Used 🌐

- [ipify](https://www.ipify.org/): For fetching public IP addresses.
- [ipinfo](https://ipinfo.io/): For geolocation and IP details.

## Libraries Used 📚

- [nlohmann/json](https://github.com/nlohmann/json): For JSON parsing.
- [cURL](https://curl.se/): For making HTTP requests.


## 🤝 Contributing:
- Contributions are welcome! If you find a bug or have a suggestion, feel free to open an issue or create a pull request.
- For any queries, mail at: alishbaabdulstealth@gmail.com
 

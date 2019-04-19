
# react-native-pttrack

## Getting started

`$ npm install react-native-pttrack --save`

### Mostly automatic installation

`$ react-native link react-native-pttrack`

### Manual installation


#### iOS

1. In XCode, in the project navigator, right click `Libraries` ➜ `Add Files to [your project's name]`
2. Go to `node_modules` ➜ `react-native-pttrack` and add `RNPttrack.xcodeproj`
3. In XCode, in the project navigator, select your project. Add `libRNPttrack.a` to your project's `Build Phases` ➜ `Link Binary With Libraries`
4. Run your project (`Cmd+R`)<

#### Android

1. Open up `android/app/src/main/java/[...]/MainApplication.java`
  - Add `import com.reactlibrary.RNPttrackPackage;` to the imports at the top of the file
  - Add `new RNPttrackPackage()` to the list returned by the `getPackages()` method
2. Append the following lines to `android/settings.gradle`:
  	```
  	include ':react-native-pttrack'
  	project(':react-native-pttrack').projectDir = new File(rootProject.projectDir, 	'../node_modules/react-native-pttrack/android')
  	```
3. Insert the following lines inside the dependencies block in `android/app/build.gradle`:
  	```
      implemation project(':react-native-pttrack')
      implementation 'com.ptmind.sdk:pttracksdk:3.0.2'
  	```
    and add the maven repositories:
    ```
      repositories {
        jcenter()
        maven { url 'https://github.com/track-sdk-android-ptmind/pttracksdk/raw/master' }
      }
    ```
4. Add the user permission in application ANdroidManifest.xml and change android:allowBackup="true" in the <application> block
    ```
      <uses-permission android:name="android.permission.INTERNET" />
      <uses-permission android:name="android.permission.ACCESS_WIFI_STATE" />
      <uses-permission android:name="android.permission.ACCESS_NETWORK_STATE" />
      <uses-permission android:name="android.permission.INTERNET" />
      <uses-permission android:name="android.permission.READ_PHONE_STATE" />
    ```

## Usage
```javascript
import {NativeModules} from 'react-native';

// TODO: What to do with the module?
NativeModules.RNPttrack.startWithAppKey("klpewupy16a9udm04za6c6", 'applestore');
NativeModules.RNPttrack.enableLogOutput();
NativeModules.RNPttrack.trackEvent('TestName', {'key1':'value1'});
```
  

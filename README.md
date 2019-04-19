
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

1. Open up `android/app/src/main/java/[...]/MainActivity.java`
  - Add `import com.reactlibrary.RNPttrackPackage;` to the imports at the top of the file
  - Add `new RNPttrackPackage()` to the list returned by the `getPackages()` method
2. Append the following lines to `android/settings.gradle`:
  	```
  	include ':react-native-pttrack'
  	project(':react-native-pttrack').projectDir = new File(rootProject.projectDir, 	'../node_modules/react-native-pttrack/android')
  	```
3. Insert the following lines inside the dependencies block in `android/app/build.gradle`:
  	```
      compile project(':react-native-pttrack')
  	```


## Usage
```javascript
import RNPttrack from 'react-native-pttrack';

// TODO: What to do with the module?
RNPttrack;
```
  

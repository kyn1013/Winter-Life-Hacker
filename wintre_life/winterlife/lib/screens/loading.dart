import 'dart:async';

import 'package:flutter/material.dart';
import 'package:weather_app/data/my_location.dart';
import 'package:weather_app/data/network.dart';
import 'package:weather_app/screens/weather_screen.dart';
import 'package:google_fonts/google_fonts.dart';

const apikey = 'c0404bdd45ac4a38479f7321044dfcd3';

class Loading extends StatefulWidget {
  @override
  _LoadingState createState() => _LoadingState();
}

class _LoadingState extends State<Loading> {
  double latitude3;
  double longitude3;
  @override
  void initState() {
    super.initState();
    Timer(Duration(seconds: 2), () {
      getLocation();
    });
  }

  void getLocation() async {
    MyLocation myLocation = MyLocation();
    await myLocation.getMyCurrentLocation();
    longitude3 = myLocation.longitude2;
    latitude3 = myLocation.latitude2;
    print(latitude3);
    print(longitude3);

    Network network = Network(
        'https://api.openweathermap.org/data/2.5/weather?lat=$latitude3&lon=$longitude3&appid=$apikey&units=metric');

    var weatherData = await network.getJsonData();
    print(weatherData);
    Navigator.push(context, MaterialPageRoute(builder: (context) {
      return WeatherScreen(
        parseWeatherData: weatherData,
      );
    }));
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: Container(
        child: Stack(children: [
          Image.asset(
            'image/house.gif',
            fit: BoxFit.cover,
            width: double.infinity,
            height: double.infinity,
          ),
          Center(
            child: Stack(children: [
              Image.asset(
                'image/bible.png',
                fit: BoxFit.fill,
                width: 300,
                height: 300,
              ),
              Padding(
                padding: const EdgeInsets.only(top: 350),
                child: Text(
                  'Winter Life',
                  style: GoogleFonts.italiana(
                    fontSize: 70.0,
                    fontWeight: FontWeight.w100,
                    color: Colors.white,
                  ),
                ),
              ),
            ]),
          ),
        ]),
      ),
    );
  }
}

import 'package:flutter/material.dart';
import 'package:flutter_svg/flutter_svg.dart';
import 'package:google_fonts/google_fonts.dart';
import 'package:timer_builder/timer_builder.dart';
import 'package:intl/intl.dart';
import 'package:weather_app/model/model.dart';
import 'package:weather_app/screens/calendar.dart';

class WeatherScreen extends StatefulWidget {
  WeatherScreen({this.parseWeatherData});
  final dynamic parseWeatherData;
  @override
  _WeatherScreenState createState() => _WeatherScreenState();
}

class _WeatherScreenState extends State<WeatherScreen> {
  Model model = Model();
  String cityName;
  int temp;
  Widget icon;
  String des;
  var date = DateTime.now();
  @override
  void initState() {
    // TODO: implement initState
    super.initState();
    updaterData(widget.parseWeatherData);
  }

  void updaterData(dynamic weatherData) {
    int condition = weatherData['weather'][0]['id'];
    des = weatherData['weather'][0]['description'];
    icon = model.getWeatherIcon(condition);
    double temp2 = weatherData['main']['temp'];
    temp = temp2.round();
    cityName = weatherData['name'];
  }

  String getSystemTime() {
    var now = DateTime.now();
    return DateFormat("h:mm a").format(now);
  }

  @override
  Widget build(BuildContext context) {
    return PageView(children: [
      Scaffold(
        body: Container(
          child: Stack(
            children: [
              Image.asset(
                'image/background.jpg',
                fit: BoxFit.cover,
                width: double.infinity,
                height: double.infinity,
              ),
              Container(
                padding: EdgeInsets.all(20.0),
                child: Column(
                    mainAxisAlignment: MainAxisAlignment.spaceBetween,
                    children: [
                      Expanded(
                        child: Column(
                            mainAxisAlignment: MainAxisAlignment.spaceBetween,
                            crossAxisAlignment: CrossAxisAlignment.start,
                            children: [
                              Column(
                                crossAxisAlignment: CrossAxisAlignment.start,
                                children: [
                                  SizedBox(
                                    height: 150.0,
                                  ),
                                  Text(
                                    '$cityName',
                                    style: GoogleFonts.lato(
                                      fontSize: 35.0,
                                      fontWeight: FontWeight.bold,
                                      color: Colors.white,
                                    ),
                                  ),
                                  Row(
                                    children: [
                                      TimerBuilder.periodic(
                                          Duration(minutes: 1),
                                          builder: (context) {
                                        print('${getSystemTime()}');
                                        return Text(
                                          '${getSystemTime()}',
                                          style: GoogleFonts.lato(
                                            fontSize: 16.0,
                                            color: Colors.white,
                                          ),
                                        );
                                      }),
                                      Text(DateFormat(' - EEEE,').format(date),
                                          style: GoogleFonts.lato(
                                            fontSize: 16.0,
                                            color: Colors.white,
                                          )),
                                      Text(
                                          DateFormat('d MMM, yyy').format(date),
                                          style: GoogleFonts.lato(
                                            fontSize: 16.0,
                                            color: Colors.white,
                                          )),
                                    ],
                                  )
                                ],
                              ),
                              Column(
                                children: [
                                  Text(
                                    '$temp\u2103',
                                    style: GoogleFonts.lato(
                                      fontSize: 70.0,
                                      fontWeight: FontWeight.w300,
                                      color: Colors.white,
                                    ),
                                  ),
                                  Row(
                                    children: [
                                      icon,
                                      SizedBox(
                                        width: 10.0,
                                      ),
                                      Text(
                                        '$des',
                                        style: GoogleFonts.lato(
                                          fontSize: 16.0,
                                          color: Colors.white,
                                        ),
                                      ),
                                    ],
                                  )
                                ],
                              ),
                            ]),
                      ),
                      Column(
                        children: [
                          Divider(
                            height: 15.0,
                            thickness: 2.0,
                            color: Colors.white30,
                          ),
                        ],
                      )
                    ]),
              )
            ],
          ),
        ),
      ),
      CalendarPage(),
    ]);
  }
}

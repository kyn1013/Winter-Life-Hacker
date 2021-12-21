import 'dart:async';

import 'package:flutter/material.dart';
import 'package:table_calendar/table_calendar.dart';

class CalendarPage extends StatefulWidget {
  @override
  _CalendarPageState createState() => _CalendarPageState();
}

class _CalendarPageState extends State<CalendarPage> {
  int d = 1;
  @override
  void initState() {
    // TODO: implement initState
    super.initState();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
        backgroundColor: Colors.white,
        body: Container(
          child: Column(
            children: [
              Expanded(
                flex: 4,
                child: Container(
                  child: FlatButton(
                    onPressed: () {
                      setState(() {
                        d++;
                        if (d == 15) {
                          d = 1;
                        }
                      });
                    },
                    child: Image.asset('image/book$d.png'),
                  ),
                ),
              ),
              Expanded(
                flex: 6,
                child: Container(
                  child: TableCalendar(
                    firstDay: DateTime.utc(2021, 10, 1),
                    lastDay: DateTime.utc(2022, 2, 28),
                    focusedDay: DateTime.now(),
                    headerStyle: HeaderStyle(
                      formatButtonVisible: false,
                      titleCentered: true,
                    ),
                  ),
                ),
              ),
            ],
          ),
        ));
  }
}

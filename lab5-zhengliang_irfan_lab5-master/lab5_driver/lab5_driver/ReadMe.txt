Lab 5 Readme.

Group members: Irfan Alahi, Zhengliang Liu.

Division of design and Implementation: We have divided the work based on independence of the project and load balancing. Which part is done by whom is given:
Irfan Alahi: 2.2(Except save and restore as they are very much dependent on the knowledge of event), 2.3,3.2
Zhengliang Liu:2.1, 2.2(save and restore part), 3.1,3.3



// answer the following questions
1. Part 2.1: Adding events to the calendar
Think about the separation of concerns in the project. 
What class/classes is responsible for the user interface of the Calendar?

CalendarInterface.

What class/classes is responsible for managing the representation and construction of the Calendar?

CalendarBuilder. For now, the concrete class that does this is FullCalendarBuilder.

Which class should handle collecting information from the user about an event?

CalendarInterface.

Which class should handle constructing and adding the event to the Calendar?

CalendarBuilder.



2. Part 2.2 Make the calendar interactive
How did you decide to efficiently search for an event by name?
We have stored the events in a multimap (along with date) using the event's name as keys. 


Which object in the project understands the structure of the Calendar? Which object should be responsible for jumping to a specific object in the Calendar?
Calendar object (both cases)


How did you design saving/restoring the calendar to/from a file? What information needs to be saved about a Calendar to successfully restore it?
We save the calendar builder type, name, starting year, years to be hold into a file. We also write every event's name, year, month, day and hour
into the same file by going through a map that we store the events (keys are their names). We restore by reading that file, build the appropriate
new builder and calendar, and then add the events back to the new calendar. We also reset the current display to the new calendar. 




3. Part 2.3 Updating the display
How a particular component in the calendar should be displayed depends on what the current display of the calendar is.
How did you implement this functionality? 

We have used chain of responsibility pattern here. A particular component in the calendar should be displayed depends on the depth from the current display.
We have modified the display method of DisplayableComponent interface to incorporate the depth.





Did you make any changes to the interfaces provided in the starter code? If so, how easy was it to 
refactor the code to match this change? 
Yes. For example, we have modified the display method of DisplayableComponent interface to incorporate the depth so that we can use chain of responsibility pattern .
It was very easy as the code is based on separation of concerns. Particularly, it seems composite pattern implements chain of responsibility pattern by default.





How does your implementation maintain flexibility and extensibility of the project? Compare this with other designs you considered.
We have used chain of responsibility here. So if we want to extend this we have to just add a newer depth. 
First, we considered to hard code the display method of all components. However, then we realize it will not be flexible. If we did like that
the flexibility and extensibility will be very hard as every time we have to change all those parts. At this point, we 
think our present implantation is very  flexible and extensible comparing to other designs we considered.





Part 3 (only answer the questions pertaining to the functionality you chose to implement)
3.1: Merging calendars
Describe the benefits of the Decorator pattern? If you used the decorator pattern, how was it applied to 
support merging calendars?
The benefit is to have less classes and only to add small pieces of extra information in a customizable fashion. We used the decorator design
pattern by adding a flag is_external and my_cal_name to indicate if the event is from an outside calendar or not and if it is，the name of the cealendar to be merged from. These are helpful for displaying the eevents that we merge from properly as it gives information for each event's associated calendar.





If you chose not to use the decorator pattern, how does your design compare with it when 
considering flexibility and extensibility of the design? 
We would probably make a new class of events that cater to the events read from other calendars, which burdens the inheritance chain and a lot of code needs to be redesigned.Or we might need to concatenate the calendar names to events and redesign the search functionality. Both are slightly more comlex. 






3.2 ToDo List
Describe your implementation? How does it support easy extensibility of the project in the future?
How is the singleton pattern used to enforce only a sigle TODO list instance?
We have used a ToDo list class which composes Task classes, that is, we have followed composite pattern.  Task class is the leaf. Both ToDo and Task class inherits from 
DisplayableComponent class. In the ToDo list class, there is a factory method which creates task and add the task to the ToDo list. Every ToDo list has a status which represent whether this is complete or todo.
We think our implantation is extensible and flexible. For example, if we change to add the functionality like part 2.3 we can easily do that using the display method and
chain of responsibility pattern.
For implantation of singleton pattern, we have made the ToDo list constructor private. A static public method is used to check whether there is already an instance of
ToDo list or not. If yes, the existing instance will be supplied, otherwise the ToDo list will be created. So there is only a single ToDo list in the program. 








3.3 Incremental Builder
What challenges did you run into while implementing this? Were any changes to the builder interface required? 
How does using the builder pattern contribute to easily being able to change how an object(calendar in this case)
is represented?
 
First, the exitsing display system is based on the Chain of Responsibility and the "depth" from current display. Hence it is 
designed recursively. However, inremental builder has no real children so we have to re-design a non-recursived display system for all the levels of display. 

Second, we need to make sure that zooming in and adding events work correctly such that these actions only happen after we build the desired components first. 

We need another class named IncrementalCalendarBuilder that inherits from the builder interface. It supports the same functionalities and the mostly same set of functions but the exact implementations are different. Many things needed to be done on the fly.

The builder pattern helps as it separates classes from their constructions and hence we only change the logic of when and how they are constructed but not the component classes themselves. 

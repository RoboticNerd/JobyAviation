<a id="readme-top"></a>

<details>
  <summary><h1>About the project</h1><br>
	This is a take-home challenge completed by Frank Sebastianelli for Joby Aviation. 
  </summary>
    <p>
      Example text here!
    </p>
		
</details>



<!-- GETTING STARTED -->



<details>
  <summary><h1> Getting Started</h1><br>
    The hardest part of any project, right? 
  </summary>
    <ul>
      <details>
        <summary>
	      <h3>Dev Environment</h3><br>
	      Just kidding, that's setting up your dev environment ^^   But here's some help:
        </summary>
		  <ul>
            <br><br><ul>
              _Note before we begin: Philosophically, this simulation was approached from a first principles perspective, there are no exotic libraries (not even for this silly attempt at a readme markdown file! (though maybe I should have... (but it was fun learning anyway.))), and nothing was "pulled in" to make my life easier (except the test framework, cause that's too much to build from scratch.)_
            </ul>
            <br> To get started you will need a dev environment configured for CMake with your choice of compiler. Provided is an overview of setting up your IDE for <strong>Windows</strong>.
            <br><br>You'll need to update your path environment variables to have paths to cmake and to your gcc or g++ compilers. I used msys2 to get my compilers, which when I loaded up onto my new laptop - decided they belonged in a new folder location, so keep an eye out. 
            <br><br>Also, I'm assuming you have git already, but for completeness you'll need that as well. Hopefully I didn't forget any. For example, on my system I have these directories added:
            <br>
            <ul>
              <br>``` C:\Program Files\Cmake\bin ```
              <br>``` C:\msys64\ucrt64\bin ```
              <br>``` C:\Program Files\Git\cmd ```
            </ul>
            <br><br>You'll also need Visual Studio installed with all the default c++ packages. I don't know if cmake or the compilers need access, but go ahead and get it to be safe.
            <br><br>We'll be using _Visual Studio Code_ from this point forward. But you can use your IDE of choice, once configured. <br>
	  </details>
	  <details>
	    <summary>
		  <h3>Final Check</h3><br>
	        Don't waste your time trying to build unless you have these dependencies all configured.
	    </summary>
        <br><ul>
          In a terminal window make sure you don't have any issues when checking your versions for each of the components we’ll be using. If you have any issues here, <strong>stop and address them first</strong>.
            <ul>
              <br>
		```Cmake --version```  
              <br> ```make --version```
            </ul>
            <br>and then for your compiler
		    <ul>
              <br>```gcc –version ``` or  ``` g++ --version```
            </ul>
          </ul><br>
	  </details>
    </ul>
</details>


<!-- USAGE -->


<details>
  <summary><h1>Usage</h1><br>
	How to run the simulator and look at the results. 
  </summary>
    <ul>
      <details>
        <summary>
          <h3>Building</h3><br>
	        How to build the repo. It's pretty chill, but here's an overview.
	    </summary>
          <ul><br>
	        To build the project.<br>
            <ul>
	          1. Clone the repo <br>
	          2. Open up a terminal window to the repo <br>
	            <ul>
                  Then you can actually build with: <br>
                  <ul>
                     ```cmake -S . -B build``` 
                  </ul>
                </ul>
	          3. Build the repo <br>
	            <ul>
                  Then you can actually build with: <br>
                  <ul>
                     ```cmake --build build``` 
                  </ul>
                </ul>
	        </ul><br>
            Your first build may take a while with the implementation of catch2 for unit testing.<br>
          </ul>
      </details>
      <details>
        <summary>
	      <h3>Running</h3><br>
	      Once it's all compiled, you can run the simulation. Here you'll see how.
	    </summary>
        <ul><br>
          To run the results, from a terminal window opened to your repo:
        <ul>
          ```.\build\Debug\mymain.exe```
        </ul>  
      </details>
      <details>
        <summary>
          <h3>Testing</h3><br>
	      Hopefully you care about testing, here we'll cover how to run/visualize your tests.
        </summary>
        <ul><br>
          To run your tests there are 2 methods I recommend.<br><br>
	  <strong>First Option:</strong><br>
	  Once built, from a terminal opened to your repo:
          <ul>
	    ```.\build\test\Debug\unit_tests.exe```
          </ul><br>
          <strong>Second Option:</strong><br>
          Use TestMate. It's a package for Visual Studio Code that provides visual cues in your editor about which test is failing. It takes like 10 seconds to add to VSC. Then, in one button click, you can see all of your tests, and see which tests and assertions failed, visually (and since I'm a visual person, I'm recommending it here). <br>
	  **:smiley:**
	</details>
  </ul>
</details>



<!-- PROBLEM OVERVIEW -->


<details>
  <summary><h1>Problem Overview</h1><br>
    An overview of the problem, the simulation and the logic employed. 
  </summary>
  <ul>
    <details>
	  <summary>
		<h3>Problem Statement</h3><br>
		The goal is to make a simulation of 20 small scale aircraft capable of carrying up to 5 passengers as they work continuously for 3 hours.
	  </summary>
      <ul><br>
	    The goal is to make a simulator that, after running for 3 hours, can provide feedback on the performance of each vehicle type. **Per vehicle type** we want to know: <br>
        <ul>
 	      - average flight time per flight <br>
	      - average distance traveled per flight <br>
	      - average time charging per charge session <br>
	      - total number of faults <br>
	      - total number of passenger miles <br>
        </ul>
	  </ul> 
	</details>
    <details>
	  <summary>
	    <h3>More Assumptions</h3><br>
	    I took some creative liberty with the assumptions, we'll outline each of those bad decisions here. (just kidding)
	  </summary>
      <ul><br>
        **Provided Assumptions:**<br>
        We were provided 3 assumptions already to assume:<br>
        <ul>
	      - Each vehicle starts the simulation with a fully-charged battery <br>
	      - Each vehicle instantaneously reaches Cruise Speed <br>
	      - Each vehicle is airborne for the full use of the battery, and is immediately in line for the charger after running out of battery power. <br>
	    </ul><br>
	    **Assumed Assumptions:**<br>
	    And those assumptions help get the ball rolling, but I found that making a few more would make the project more fun.<br>
        <ul>
          - We will be simulating “last mile” human delivery to and from a large airport.<br>
        </ul>
	    <details>
	      <summary>
	        &nbsp;&nbsp;&nbsp;&nbsp;- I will use Houston, TX as the reference city. **Why:**
	      </summary>
          <ul><ul>
            The long distances suggest higher uber costs, which suggests a better opportunity for direct flights. Further, the longer uber times would probably make sense for having a better user experience (ie its easier to cut a 60 minute drive time in half than a 10 minute drive time (once you consider, takeoff, taxi, ingress/egress etc)). Also my intimate knowledge of the city helps understand the population density to come up with a reasonable max distance for passengers. Still, long flight times are arguably worse for EV aircraft, so it might be interesting to see what happens?
          </ul></ul>
	    </details>
        <ul>
	      - Houston has 2 international airports, we’ll assume there is only one airport about equidistant between the 2 and a 32km (20mi) radius will cover much of the population. <br>
	      - We assume all passengers unload and load instantly.
	    </ul>
	    <details>
	      <summary>
	        &nbsp;&nbsp;&nbsp;&nbsp;- We assume the passenger demand/load is so high,** that:**<br>
	      </summary>
          <ul><ul>
	        - Passengers are available instantly during the 3 hour departure - for departing the airport and returning.<br>
		    - And even for smaller aircraft, a smaller passenger group is available instantly.<br>
		    - These passenger groups are equally likely to be any number of size less than the vehicle max. <br>
		    - These passengers refuse to ride with anyone else. <br>
          </ul></ul>
	    </details>
        <ul>
          - Every aircraft in the sky today is capable of flying with multiple faults. Still, at 3 faults we will remove an aircraft from service.<br>
	      - We assume that the aircraft always has enough battery to fly back, so it won't leave unless it has 32km of range or more. (notice a problem? check the roadmap below)
        </ul><br>
        This list is not comprehensive, there might be more, but these are the assumptions I wrote down along the way.
      </ul>
    </details>
    <details>
      <summary>
        <h3>Implimentation</h3><br>
	    Here we'll share the logic employed in the simulation.
      </summary>
      <ul>
	      Such much logic. <br><br>
        <h4> High Level Overview:</h4>
        <ul>
          First we have a few object types.<br>
          <ul><strong>
            - Passengers <br>
            - Passenger Groups <br>
            - Vehicles <br>
            - Vehicle Fleet <br>
          </ul></strong>
          First, we can put passengers into Passenger Groups.<br>
          Then, we can put Passenger Groups into Vehicles.<br>
          Finally, we can have Vehicles be a part of a Vehicle Fleet.<br><br>
          I use a state machine to control the different states of the vehicles.<br><br>
        </ul>
        <h4> Medium Level Overview:</h4>
        <ul>
          <strong>Passenger Groups: </strong>These can house a number of passengers along with some stats. They can also apparate and disapparate a new batch of passengers - with a random group size (that fits inside the vehicle), and a random distance from the airport (that's less than the 32km "limit").<br><br>
          <strong>Vehicles:</strong> These store all prescribed vehicle data, Passenger Groups, as well as any other relevant data pertaining to an individual vehicle. They also house the statemachine and each vehicle can be simulated individually.<br><br>
          <strong>Vehicle Fleet:</strong> This is a pretty simple object, as much of the complexity has been abstracted away by now. It serves to manage and coordinate charging station use, and to summarize fleet metrics. <br><br>
          <strong>main.cpp:</strong> To simulate any fleet size requires only a few lines of code. Then you itterate until the simulation is complete. (1 minute step size today). Main.cpp also acts as the "example".<br><br>
      </ul>
      <h4> Detailed Level Overview:</h4>
        <ul>
          <strong>Lets talk in person ;) </strong>
      </ul>
    </details>
  </ul>
</details>


<br><br><br>Example Results/Output:
```
Vehicle Types:                                  [ Alpha   Bravo   Charlie Delta   Echo    ];
Average flight time per flight (min):           [ 3       4       3       4       15      ];
Average distance per flight (km):               [ 11.6165 12.7962 15.2422 9.71086 12.7238 ];
Average time charging per charge session (min): [ 0       39      17      0       0       ];
Total faults (count):                           [ 0       0       0       0       0       ];
Total passenger kilometers (km):                [ 3057.73 1939.21 1922.59 639.71  291.289 ];
```

<br><br>
<details>
  <summary>Future work</summary><br>
    <ul>
      - Presently it takes 1 minute to unload/load passengers. It’s effectively wasted. But this is closer to real life. So we’ll leave the bug but call it a “feature”.<br><br>
      - Only incurring faults during flying. While it feels more likely, can't faults arrise during charging too? Probably at a different failure rate?<br><br>
      - Presently situations can arrise where you have charge left, and could have done a shorter route.<br><br>
      - Passenger requests should come from around the city with gps coordinates, and would be neat to incorporate loss with having to fly to pickup a passenger on the way to the airport.<br> <br>
    </ul>
</details>
<p align="right">(<a href="#readme-top">back to top</a>)</p>

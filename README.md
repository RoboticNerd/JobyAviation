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

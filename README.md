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

# Synchronization tool

The "Synchronization Tool" is a C++ based utility that facilitates one-way synchronization between two directories: the `Source` directory and the `Replica` directory. This tool
ensures that the contents of the Replica directory remain fully identical to the Source directory.

## Usage
1. Clone this repository:
    
        git clone https://github.com/puklu/Synchronize-directories-cpp.git

2. Navigate to the project folder:

   After cloning the repository, navigate to the location where the project is cloned.

3. To run the tool, 
    
         ./bin/main -srcdir <path/to/source-dir> -repdir <path/to/replica-dir> -interval <sync_interval>

   Rum the tool with appropriate command-line arguments to initiate synchronization. 

   The tool accepts the following parameters:

   <u><strong>Mandatory</strong></u>
 
   1. `-srcdir`: Path to the `Source` directory.

   <u><strong>Optional but recommended</strong></u>

   2. `-repdir`: Path to the `Replica` directory.
   
         Default location is the root of this project if not provided by the user.

   3. `-interval`: Interval (in seconds) at which synchronization should be performed. 
      
        Default value is 10 seconds if not provided by the user.

  
   Example 1 (with all the parameters):

         ./bin/main -srcdir <path/to/source-dir> -repdir <path/to/replica-dir> -interval <sync_interval>

   Example 2 (with only the mandatory parameter):

         ./bin/main -srcdir <path/to/source-dir>

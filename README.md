# Peer-to-Peer Group Based File Sharing System

### Prerequisites
Socket Programming, SHA1 hash, Multi-threading in C++
### Goal
In this assignment, you need to build a group based file sharing system where users can share, download files from the group they belong to. Download should be parallel with multiple​ pieces from multiple peers.
### Note:
- You have to divide the file into logical  “pieces”, wherein the size of each piece should be 512KB.
- SHA1 : Suppose the file size is 1024KB, then divide it into two pieces of 512KB each and take SHA1 hash of each part, assume that the hashes are HASH1 & HASH2 then the corresponding hash string would be H1H2 , where H1 & H2 are starting 20 characters of HASH1 & HASH2 respectively and hence H1H2 is 40 characters.
- Authentication for login needs to be done

### Architecture Overview:
The Following entities will be present in the network :<br/>
**1. Server(or Tracker)( 1 tracker system) :**<br/>
     Maintain information of clients with their files(shared by client) to assist the clients for the communication between peers<br/>
**2. Clients:**<br/>
**a.** User should create an account and register with tracker<br/>
**b.** Login using the user credentials<br/>
**c.** Create Group and hence will become owner of that group<br/>
**d.** Fetch list of all Groups in server<br/>
**e.** Request to Join Group<br/>
**f.** Leave Group<br/>
**g.** Accept Group join requests (if owner)<br/>
**h.** Share file across group: Share the filename and SHA1 hash of the complete file as well as piecewise SHA1 with the tracker<br/>
**i.** Fetch list of all sharable files in a Group<br/>
**j.** Download file<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**i.** Retrieve peer information from tracker for the file<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**ii.** Core Part: Download file from multiple peers (different pieces of file from
different peers -  piece selection algorithm ) simultaneously and all the files which client downloads will be shareable to other users in the same group.<br/>
**k.** Show downloads<br/>
**l.** Stop sharing file<br/>
**m.** Stop sharing all files(Logout)<br/>
**n.** Whenever client logins, all previously shared files before logout should
automatically be on sharing mode<br/>

### How to compile project
1. go to client directory
   * ```g++ client.cpp -o client -lssl -lcrypto -lpthread```
2. go to server directory
   * ```g++ server.cpp -o server -lpthread```

### How to Run project
#### To run the Server
```
./server <my_server_ip> <my_server_port>
eg : ./server 127.0.0.1 5000
```
#### To run the Client

```
./client <CLIENT_IP> <CLIENT_PORT> <SERVER_IP> <SERVER_PORT>
```
* creating client1 on new terminal with socket : 127.0.0.1:6000 <br/>
eg : ```./client 127.0.0.1 6000 127.0.0.1 5000```

* creating client2 on another terminal with socket : 127.0.0.1:7000 <br/>
eg : ```./client 127.0.0.1 7000 127.0.0.1 5000```

#### Command/Functionality on Clinent side 
 **1. Create User Account :** 
 ```
 create_user <user_id> <passwd>
 ```
 **2. Login :**
 ```
 login <user_id> <passwd>
 ```
 **3. Create Group  :**
 ```
 create_group <group_id>
 ```
 **4. Join Group :**
 ```
 join_group <group_id>
 ```
 **5. Leave Group  :**
 ```
 leave_group <group_id>
 ```
 **6. List Pending Request :**
 ```
 requests list_requests <group_id>
 ```
 **7. Accept Group Joining Request :**
 ```
 accept_request <group_id> <user_id>
 ```
 **8. List All Group In Network :**
 ```
 list_groups
 ```
 **9. List All sharable Files In Group :**
 ```
 list_files <group_id>
 ```
 **10. Upload File :**
 ```
 upload_file <file_path> <group_id>
 eg.: upload_file /home/rishabh/F/video.mp4 my_grp
 ```
 **11. Download File :**
 ```
 download_file <group_id> <file_name> <destination_path>
 eg.: download_file my_grp video.mp4 /home/rishabh/D/
 ```
 **12. Logout :**
 ```
 logout
 ```
 **13. Show_downloads :**
 ```
 show_downloads
 ```
 Output format:
[D] [grp_id] filename
[C] [grp_id] filename
D(Downloading), C(Complete)
 **14. Stop sharing :**
 `stop_share <group_id> <file_name>`
 
 #### Assumption
* Enter absolute path for files.

   
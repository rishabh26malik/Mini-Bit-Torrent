#include "header.h" 
#define PORT 8080 
using namespace std;
CLIENT client[10];
int k=0;
map <int, int> sock2idx;

vector <vector<down_file>> downloaded_files(100, vector<down_file> (100));
map <string, int> file_2_idx;

string server_ip;
int server_port;
string shareHASH;
int client_port;
string client_ip;
int myPort;
ofstream output;
int m=0;

void tokenize(string command, vector <string> &cmds){
    command+=" ";
    string str="";
    int i,n=command.length();
    for(i=0;i<n;i++){
        if(command[i]!=' '){
            str+=command[i];
        }
        else{
            cmds.push_back(str);
            str="";
        }
    }
}

void create_user(string command, vector <string> cmd, int sock){
    if(cmd.size() != 3){
        cout<<"INVALID NO. OF ARGS\n";
        return;
    }
    int len;
    char buffer[1024] = {0};
    while(1){
        len=command.length();
        char send_cmd[len];
        strcpy(send_cmd, command.c_str());
        send(sock , send_cmd , strlen(send_cmd) , 0 );
        int valread = read( sock , buffer, 1024);
        string replyStr(buffer);
        printf("%s\n",buffer );
        if(replyStr=="USER NAME ALREADY IN USE"){
            string usrname;
            cout<<"enter username again : ";
            cin>>usrname;
            cmd[1]=usrname;
            command="create_user "+usrname+" "+cmd[2];
        }
        else
            break; 
    }
}

void login(string command, vector <string> cmd, int sock){
    if(cmd.size() != 3){
        cout<<"INVALID NO. OF ARGS\n";
        return;
    }
    int len,attempts=4;
    while(1){
        if(attempts==0){
            cout<<"all attempts exhausted...!!! so awk....!!!\n";
            break;
        }
        len=command.length();
        char send_cmd[len];
        strcpy(send_cmd, command.c_str());
        fflush(stdout);
        send(sock , send_cmd , strlen(send_cmd) , 0 );
        char buffer[1024] = {0};
        int valread = read( sock , buffer, 1024);
        string replyStr(buffer);
        printf("%s\n",buffer );
        if(replyStr=="USERNAME OR PSW IS WRONG"){
            string usr_psw;
            cout<<"ENTER USERNAME PASSWORD AGAIN : ";
            getline(cin,usr_psw);
            command="login "+usr_psw;
        }
        else
            break; 
        attempts--;
    }
}

void create_group(string command, vector <string> cmd, int sock){
    if(cmd.size() != 2){
        cout<<"INVALID NO. OF ARGS\n";
        return;
    }
    int len,attempts=4;
    while(1){
        if(attempts==0){
            cout<<"all attempts exhausted...!!! so awk....!!!\n";
            break;
        }
        len=command.length();
        char send_cmd[len];
        strcpy(send_cmd, command.c_str());
        fflush(stdout);
        send(sock , send_cmd , strlen(send_cmd) , 0 );
        char buffer[1024] = {0};
        int valread = read( sock , buffer, 1024);
        string replyStr(buffer);
        printf("%s\n",buffer );
        if(replyStr=="GROUP ID NOT UNIQUE"){
            string grpId;
            cout<<"ENTER GROUP ID AGAIN : ";
            getline(cin,grpId);
            command="create_group "+grpId;
        }
        else
            break; 
        attempts--;
    }
}



void join_group(string command, vector <string> cmd, int sock){
    if(cmd.size() != 2){
        cout<<"INVALID NO. OF ARGS\n";
        return;
    }
    int len,attempts=4;
    while(1){
        if(attempts==0){
            cout<<"all attempts exhausted...!!! so awk....!!!\n";
            break;
        }
        len=command.length();
        char send_cmd[len];
        strcpy(send_cmd, command.c_str());
        fflush(stdout);
        send(sock , send_cmd , strlen(send_cmd) , 0 );
        char buffer[1024] = {0};
        int valread = read( sock , buffer, 1024);
        string replyStr(buffer);
        printf("%s\n",buffer );
        if(replyStr=="NO SUCH GROUP"){
            string grpId;
            cout<<"ENTER GROUP ID AGAIN : ";
            getline(cin,grpId);
            command="join_group "+grpId;
        }
        else
            break; 
        attempts--;
    }
}

void list_requests(string command, vector <string> cmd, int sock){
    if(cmd.size() != 2){
        cout<<"INVALID NO. OF ARGS\n";
        return;
    }
    int len,attempts=4;
    while(1){
        if(attempts==0){
            cout<<"all attempts exhausted...!!! so awk....!!!\n";
            break;
        }
        len=command.length();
        char send_cmd[len];
        strcpy(send_cmd, command.c_str());
        fflush(stdout);
        send(sock , send_cmd , strlen(send_cmd) , 0 );
        char buffer[1024] = {0};
        int valread = read( sock , buffer, 1024);
        string replyStr(buffer);
        printf("%s\n",buffer );
        if(replyStr=="NO SUCH GROUP"){
            string grpId;
            cout<<"ENTER GROUP ID AGAIN : ";
            getline(cin,grpId);
            command="list_requests "+grpId;
        }
        else
            break; 
        attempts--;
    }
}

void leave_group(string command, vector <string> cmd, int sock){
    if(cmd.size() != 2){
        cout<<"INVALID NO. OF ARGS\n";
        return;
    }
    int len,attempts=4;
    while(1){
        if(attempts==0){
            cout<<"all attempts exhausted...!!! so awk....!!!\n";
            break;
        }
        len=command.length();
        char send_cmd[len];
        strcpy(send_cmd, command.c_str());
        fflush(stdout);
        send(sock , send_cmd , strlen(send_cmd) , 0 );
        char buffer[1024] = {0};
        int valread = read( sock , buffer, 1024);
        string replyStr(buffer);
        printf("%s\n",buffer );
        if(replyStr=="NO SUCH GROUP"){
            string grpId;
            cout<<"ENTER GROUP ID AGAIN : ";
            getline(cin,grpId);
            command="leave_group "+grpId;
        }
        else
            break; 
        attempts--;
    }
}

void accept_request(string command, vector <string> cmd, int sock){
    if(cmd.size() != 3){
        cout<<"INVALID NO. OF ARGS\n";
        return;
    }
    int len,attempts=4;
    while(1){
        if(attempts==0){
            cout<<"all attempts exhausted...!!! so awk....!!!\n";
            break;
        }
        len=command.length();
        char send_cmd[len];
        strcpy(send_cmd, command.c_str());
        fflush(stdout);
        send(sock , send_cmd , strlen(send_cmd) , 0 );
        char buffer[1024] = {0};
        int valread = read( sock , buffer, 1024);
        string replyStr(buffer);
        printf("%s\n",buffer );
        if(replyStr=="INVALID GROUP OR USER ID"){
            string grp_usr_Id;
            cout<<"ENTER GROUP ID AND USER ID AGAIN : ";
            getline(cin,grp_usr_Id);
            command="accept_request "+grp_usr_Id;
        }
        else
            break; 
        attempts--;
    }
}

void list_groups(string command, vector <string> cmd, int sock){
    if(cmd.size() != 1){
        cout<<"INVALID NO. OF ARGS\n";
        return;
    }
    int len=command.length();
    char send_cmd[len];
    strcpy(send_cmd, command.c_str());
    fflush(stdout);
    send(sock , send_cmd , strlen(send_cmd) , 0 );
    char buffer[1024] = {0};
    int valread = read( sock , buffer, 1024);
    string replyStr(buffer);
    printf("%s\n",buffer );
}

string getSHA_Hash(vector <string> cmd, int &total_chunks/*, vector <string> &pieces*/){
    char filepath[100];
    strcpy(filepath, cmd[1].c_str());
    string hash="", piece_wise="";
    struct stat sb;
    int piece_size=512*1024, total_pieces, size, last_piece;
    int no_of_pieces;
    if (stat(filepath, &sb) == -1) {
        perror("stat : no such file or wrong path\n");
        exit(EXIT_FAILURE);
    }
    size=sb.st_size;
    total_pieces = size/piece_size;
    if(size % piece_size == 0)
        last_piece = 512*1024;
    else{
        total_pieces++;
        last_piece = size % piece_size;
    }
    no_of_pieces=total_pieces;
    cout<<size<<" "<<total_pieces<<" "<<last_piece<<endl;
    total_chunks=total_pieces;
    ifstream input_file;
    input_file.open(filepath);
    unsigned char input[piece_size], SHA_hash[20*total_pieces];
    while(total_pieces--){
        input_file.read((char*)input, piece_size);
        if(total_pieces > 1){
            SHA1(input, piece_size , SHA_hash);
        }
        else{
            SHA1(input, last_piece , SHA_hash);
        }
        string piece((char*)SHA_hash);
        hash += piece;  
        piece_wise += piece+" ";        
    }
    return hash;
}

void upload_file(string command, vector <string> cmd, int sock){
    if(cmd.size() != 3){
        cout<<"INVALID NO. OF ARGS\n";
        return;
    }
    int total_chunks=0;
    string SHA_hash=getSHA_Hash(cmd, total_chunks);    
    string filename="";
    int i=cmd[1].length()-1;
    while(cmd[1][i]!='/'){
        filename=cmd[1][i]+filename;
        i--;
    }
    struct stat fstatus;
    stat(filename.c_str(), &fstatus);
    long int total_size = fstatus.st_size;
    command="upload_file "+filename+" "+cmd[2]+" "+to_string(total_chunks)+" "+to_string(total_size)+" "+to_string(SHA_hash.length())+" "+SHA_hash;
    int len=command.length();
    char send_cmd[len];
    strcpy(send_cmd, command.c_str());
    fflush(stdout);
    send(sock , send_cmd , strlen(send_cmd) , 0 );
    char buffer[1024] = {0};
    int valread = read( sock , buffer, 1024);
    string replyStr(buffer);
    printf("%s\n",buffer );
}

void list_files(string command, vector <string> cmd, int sock){
    if(cmd.size() != 2){
        cout<<"INVALID NO. OF ARGS\n";        
    }
    int len=command.length();
    char send_cmd[len];
    strcpy(send_cmd, command.c_str());
    fflush(stdout);
    send(sock , send_cmd , strlen(send_cmd) , 0 );
    char buffer[1024] = {0};
    int valread = read( sock , buffer, 1024);
    string replyStr(buffer);
    printf("%s\n",buffer ); 
}

void * client1(void *temp){
    string data=*(string*)temp;	
	cout<<"--->>> "<<data<<endl;
	vector <string> tokens;
	tokenize(data, tokens);
	int port=stoi(tokens[0]);
	int client_socket;
    client_socket=socket(AF_INET,SOCK_STREAM,0);
    if(client_socket==-1){
        printf("Socket creation error %d\n",errno);
        return 0;
    }
    struct sockaddr_in server_address;
    char buffer[512*1024]={0};
    if(inet_pton(AF_INET,"127.0.0.1",&server_address.sin_addr)==-1){
        printf("Invalid Address:%d\n",errno);
    }
    server_address.sin_family=AF_INET;
    server_address.sin_port=htons(port);        
    int addrlen=sizeof(server_address);
    int socket=connect(client_socket,(struct sockaddr*)&server_address,addrlen);
    if(socket==-1){
        printf("Connect error:%d\n",errno);
        return 0;
    }
    printf("Thread Connected\n");    
    write(client_socket,data.c_str(),data.length());
    //write(client_socket,msg,strlen(msg));
    ifstream file1(tokens[3].c_str(), ifstream::binary);
    if (!file1)
    {
        cout << "Can't Open file1  : "<< endl;
        //return "-1";
    }
	
    
    long int total_size = stol(tokens[4], nullptr, 10);;//fstatus.st_size;
    cout<<total_size<<endl;
    long int chunk_size = 64*1024;

    int total_chunks = total_size / chunk_size;
    int last_chunk_size = total_size % chunk_size;

    if (last_chunk_size != 0) // if file1 is not exactly divisible by chunks size
    {
        ++total_chunks; // add last chunk to count
    }
    else //when file1 is completely divisible by chunk size
    {
        last_chunk_size = chunk_size;
    }
    cout<<total_chunks<<" "<<last_chunk_size<<endl;



    int i=stoi(tokens[1]), start=stoi(tokens[1]), end=stoi(tokens[2]), idx=file_2_idx[tokens[3]];
    start*=512*1024;
    end=start+end*512*1024;
    //  ******************************* MULTI SEED DOWNLOAD **************************************
    
    int read_last_chunk=total_size % (64*1024);
    cout<<read_last_chunk<<endl;
    int read_size=64*1024;
    //end=start+end*512*1024;
    while(start < end && start < total_size){
        int slab=end-start;
        if(slab % read_size != 0){
            read_size=read_last_chunk;
        }
        downloaded_files[idx][i].chunk=(char*)malloc(sizeof(char)*read_size);
        int valread=read(client_socket, downloaded_files[idx][i].chunk, read_size);
        cout<<valread<<"-"<<tokens[0]<<endl;
        output.seekp(start,ios::beg);
        output.write (downloaded_files[idx][i].chunk, read_size);
        i++;
        start += read_size;
    }
    //  ******************************************************************************************* 

    //  ******************************* SINGLE SEED DOWNLOAD **************************************
    /*
    int i, start=stoi(tokens[1]), end=stoi(tokens[2]), idx=file_2_idx[tokens[3]];
    start*=512*1024;
    end=start+end*512*1024;

    ofstream outfile;
    string destpath1=tokens[5]+tokens[3];
    char *d_path1 = new char[destpath1.length() + 1];
    strcpy(d_path1, destpath1.c_str());
    outfile.open(d_path1);

    int read_last_chunk=total_size % (64*1024);
    cout<<read_last_chunk<<endl;
    int read_size=64*1024;
    while(start < end && start < total_size){
    	int slab=end-start;
    	if(slab % read_size != 0 ){
    		read_size=read_last_chunk;
    	}
    	downloaded_files[idx][i].chunk=(char*)malloc(sizeof(char)*read_size);
        int valread=read(client_socket, downloaded_files[idx][i].chunk, read_size);
        cout<<valread<<"-"<<tokens[0]<<endl;
        //myfile.write(downloaded_files[idx][i].chunk, read_size);
    	
        outfile.seekp(start,ios::beg);
        outfile.write (downloaded_files[idx][i].chunk, read_size);

    	start += read_size;
    }
    outfile.close();*/
    //  *******************************************************************************************

    close(client_socket);
    return NULL;

}


void download_file(string command, vector <string> cmd, int sock){
    if(cmd.size() != 4){
        cout<<"INVALID NO. OF ARGS\n";
        return;
    }
    file_2_idx[cmd[2]]=m;
    m++;
    int len=command.length();
    char send_cmd[len];
    strcpy(send_cmd, command.c_str());
    fflush(stdout);
    send(sock , send_cmd , strlen(send_cmd) , 0 );
    char buffer[1024] = {0};
    int valread = read( sock , buffer, 1024);
    string replyStr(buffer);
    printf("%s\n",buffer ); 

    if(replyStr=="NO USER CREATED" || replyStr=="U R NOT LOG IN"   || replyStr=="NO SUCH GROUP"
    		   || replyStr=="U R NOT A PART OF THIS GROUP"   || replyStr=="FILE_NOT_AVAILABLE" ){
        return;
    }
    // TILL HERE, GOT INFO OF SEEDS
    ////////////////
    int i, chunks;
    len=replyStr.length();
    vector <string> seeds_ip;
    vector <int> seeds_port;
    string tmp="";
    for(i=0;i<len;i++){
        if(replyStr[i]==','){
            seeds_ip.push_back(tmp);
            tmp="";
        } 
        else if(replyStr[i]=='|'){
            //cout<<"----\n";
            seeds_port.push_back(stoi(tmp));
            tmp="";
        }
        else if(replyStr[i]=='-')
            break;
        else            
            tmp+=replyStr[i];
    }
    chunks=stoi(tmp);
    cout<<chunks<<" "<<replyStr.length()<<endl;
    i++;
    string aa=replyStr.substr(i,5);
    tmp="";
    cout<<len<<" "<<"i - "<<i<<endl;
    while(i<len){
    	cout<<replyStr[i];
    	tmp+=replyStr[i];
    	i++;
    }
    cout<<"\nfile size - "<<tmp<<endl;
    long int size_of_file=stol(tmp, nullptr, 10);
    cout<<size_of_file<<endl;
    len=seeds_port.size();
    pthread_t thread_id[len];
	int x=chunks/len;
    int start_chk=0;

    vector<string> passDetails(len);
    /*
    // ******** FOR DOWNLOADING FROM ONLY 1 SEED ON FCFS BASIS **********

    string str=to_string(seeds_port[0])+" "+to_string(start_chk)+" "+to_string(chunks)+" "+cmd[2]+" "+to_string(size_of_file)+" "+cmd[3];
	passDetails[0]=str;
	if (pthread_create(&thread_id[0], NULL, client1 , (void *)&passDetails[0]) < 0)
    {
        perror("\ncould not create thread in download_file\n");
    }
    pthread_join(thread_id[0],NULL);
    // *****************************************************************
    */



    cout<<"chunks - "<<chunks<<endl;
    //cout<<"joined"<<endl;
    for(i=0;i<len;i++){
    	string str="";
    	if(i==len-1){
            cout<<start_chk<<" "<<chunks<<" "<<chunks-start_chk<<endl;
    		str=to_string(seeds_port[i])+" "+to_string(start_chk)+" "+to_string(chunks-start_chk)+" "+cmd[2]+" "+to_string(size_of_file)+" "+cmd[3];	
    	}
    	else{
            cout<<start_chk<<" "<<chunks<<" "<<x<<endl;
	    	str=to_string(seeds_port[i])+" "+to_string(start_chk)+" "+to_string(x)+" "+cmd[2]+" "+to_string(size_of_file)+" "+cmd[3];
        }
    	passDetails[i]=str;
    	start_chk+=x;
    	//cout<<passDetails[i].c_str()<<endl;
    }

    string destpath1=cmd[3]+cmd[2];
    char *d_path1 = new char[destpath1.length() + 1];
    strcpy(d_path1, destpath1.c_str());
    output.open(d_path1);

    for(i=0;i<len;i++){   
        if (pthread_create(&thread_id[i], NULL, client1 , (void *)&passDetails[i]) < 0)
        {
            perror("\ncould not create thread in download_file\n");
        }
    }

    cout<<"AFTER LOOP\n";

    m++;
    for(i=0;i<len;i++){
        pthread_join(thread_id[i],NULL);
        cout<<"join - "<<i<<endl;
    }
    output.close();
    cout<<"AFTER JOIN\n";
}


void execute_cmd(string command, vector <string> cmd, int sock){
    string reply;
    if(cmd[0]=="create_user"){
        create_user(command, cmd, sock);
    }
    else if(cmd[0]=="login"){
        login(command, cmd, sock);  
    }
    else if(cmd[0]=="create_group"){
        create_group(command, cmd, sock);   
    }
    else if(cmd[0]=="join_group"){
        join_group(command, cmd, sock); 
    }
    else if(cmd[0]=="list_requests"){
        list_requests(command, cmd, sock);  
    }
    else if(cmd[0]=="leave_group"){
        leave_group(command, cmd, sock);    
    }
    else if(cmd[0]=="list_groups"){
        list_groups(command, cmd, sock);    
    }
    else if(cmd[0]=="accept_request"){
        accept_request(command, cmd, sock);
    }
    else if(cmd[0]=="upload_file"){
        upload_file(command, cmd, sock);
    }
    else if(cmd[0]=="list_files"){
        list_files(command, cmd, sock);
    }
    else if(cmd[0]=="download_file"){
        download_file(command, cmd, sock);
    }
    else{
        cout<<"INVALID COMMAND\n";
    }   
}


void * acceptCon(void * client_socket1){
    int client_socket=*(int*)client_socket1;
    free(client_socket1);
    char buffer[1024]={0};
    int valread=read(client_socket,buffer,1024);
    cout<<buffer<<endl;
    string command(buffer);
    vector <string> tokens;
    tokenize(command, tokens);
    int piece_size=512*1024, total_pieces=stoi(tokens[2]);
    ifstream input_file;
    input_file.open(tokens[3].c_str());
    ifstream file1(tokens[3].c_str(), ifstream::binary);
    if (!file1)
    {
        cout << "Can't Open file1  : "<< endl;
        //return "-1";
    }
	
    long int total_size = stol(tokens[4],nullptr, 10);//fstatus.st_size;
    cout<<total_size<<endl;
    long int chunk_size = 512*1024;

    int total_chunks = total_size / chunk_size;
    int last_chunk_size = total_size % chunk_size;

    if (last_chunk_size != 0) 
    {
        ++total_chunks; 
    }
    else 
    {
        last_chunk_size = chunk_size;
    }
    cout<<total_chunks<<" "<<last_chunk_size<<endl;
    
    //  *********************  SINGLE SEED SENDING  *********************************
    /*int i, start=stoi(tokens[1]), end=stoi(tokens[2]), m=stoi(tokens[2]);
    start*=512*1024;
    end=start+end*512*1024;
    int read_last_chunk=total_size % (64*1024);
    cout<<read_last_chunk<<endl;
    int read_size=64*1024;
    for(i=0;i<m;i++){
        int slab=end-start;
        if(slab % read_size != 0 ){
            read_size=read_last_chunk;
        }

    }*/

    //  *******************************************************************************************

    //  *********************  MULTI SEED SENDING  *********************************
    int i, start=stoi(tokens[1]), end=stoi(tokens[2]);
    start*=512*1024;
    end=start+end*512*1024;
    int read_last_chunk=total_size % (64*1024);
    cout<<read_last_chunk<<endl;
    int read_size=64*1024;
    while(start < end && start < total_size){
    	int slab=end-start;
    	if(slab % read_size != 0 ){
    		read_size=read_last_chunk;
    	}
 		char *chunk_data = new char[read_size];
        file1.seekg(start,ios::beg);
        file1.read(chunk_data, read_size);
        //myfile.write(chunk_data, read_size);
        send(client_socket , chunk_data , read_size , 0 );
        
    	start += read_size;
    }
    file1.close();
    //  *******************************************************************************************
    //myfile.close();

    close(client_socket);
    return NULL;
}


void * server(void *temp){
    int server_socket;
    int port=*(int*)temp;
    struct sockaddr_in address;
    char buffer[1024]={0};
    int opt=1;
    
    server_socket=socket(AF_INET,SOCK_STREAM,0);
    if(server_socket==-1){
        cout<<"Socket creation error "<<errno<<endl;
        return 0;
    }

    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_addr.s_addr=INADDR_ANY;
    address.sin_family=AF_INET;
    address.sin_port=htons(port);
    int addrlen=sizeof(address);
    if(bind(server_socket,(const struct sockaddr *)&address,addrlen)==-1){
        printf("bind error:%d\n",errno);
        return 0;
    }
    if(listen(server_socket,4)==-1){
        printf("Listen error:%d\n",errno);
        return 0;
    }

    printf("Listening\n");
    while(1){
        struct sockaddr_in client;
        socklen_t client_len=sizeof(client);
        int client_socket=accept(server_socket,(struct sockaddr*)&client,&client_len);
        if(client_socket==-1){
            printf("Accept error:%d\n",errno);
            return 0;
        }
        cout<<ntohs(client.sin_port)<<"  "<<inet_ntoa(client.sin_addr)<<endl;
        pthread_t t;
        struct sockaddr_in *temp=(struct sockaddr_in *)malloc(sizeof(client));
        *temp=client;
        int *client_soc=(int*)malloc(sizeof(int));
        *client_soc=client_socket;
        pthread_create(&t,NULL,acceptCon,client_soc);
    }
    close(server_socket);
    return 0;
}


int main(int argc, char const *argv[])
{
    pthread_t t1,t2;
    if (argc != 5)
    {
        cout << "Invalid Argument in client!!!" << endl;
    }
    else
    {  
        pthread_t thread_id;
        string ip1(argv[1]);
        string port1(argv[2]);
        int myPort=stoi(port1);
        ip1=ip1+" "+port1;
        char passIP_port[ip1.length()];
        strcpy(passIP_port, ip1.c_str());
        pthread_create(&t1,NULL,server,&myPort);
        
        //socket programming on client side
        int sock = 0;
        struct sockaddr_in serv_addr, my_addr;
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            printf("\n Socket creation error in client side\n");
            return -1;
        }

        /*my_addr.sin_family = AF_INET; 
        my_addr.sin_addr.s_addr = INADDR_ANY; 
        my_addr.sin_port = htons(atoi(argv[2]));

        if (bind(sock, (struct sockaddr*) &my_addr, sizeof(struct sockaddr_in)) == 0) 
            printf("Binded Correctly\n"); 
        else
            printf("Unable to bind\n");*/

        memset(&serv_addr, '0', sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(atoi(argv[4]));      //trackersocket1.port

        //Convert IPv4 and IPv6 addresses from text to binary form
        if (inet_pton(AF_INET, argv[3] , &serv_addr.sin_addr) <= 0)         //trackersocket1.ip
        {
            printf("\nClient File  : Invalid address/ Address not supported \n");
            return -1;
        }
        if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        {
            printf("\nConnection Failed in client side\n");
            return -1;
        }
        cout<<"connected\n";
        send(sock , argv[2] , strlen(argv[2]) , 0 );    //send client's server is running sock port no
        //continuously listening to client for his entring command        
        while(1){
            string command;
            getline(cin, command);
            vector <string> cmd;
            tokenize(command, cmd);
            execute_cmd(command, cmd, sock); 
        }        
    }
    return 0;
}

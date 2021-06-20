/* 
test primeri: 

3
Pneuma - Drum Cover
Danny Carey
225
1040
3
2
3840
0
21042020

output: Pneuma - Drum Cover - Danny Carey - 21042020 - 225 - 75465
-----------------
5
5
1
Through the Fire and Flames
Herman Li
442
45
3
5
3
Through the Fire and Flames - Remix
Herman Li
442
1020
3
5
1920
1
21042011
1
Pneuma
Tool
225
45
3
2
2
Sober - Music Video
Fred Stuhr
183
350
1080
1
3
Pneuma - Drum Cam
Danny Carey
225
1040
3
2
3840
0
21042020

output: Through the Fire and Flames - Remix - Herman Li - 442 - 1020 - 56023.5
-------------------
*/

#include<iostream>
#include<cstring>
using namespace std;
enum Format {
    mp3=0,
    wav,
    ogg,
    flac
};
enum Kompresija {
    x264 = 0,
    Theora,
    AV1
};

class MediaSegment {
protected:
    char naslov[101];
    char avtor[101];
    int vremetraenje;
    int golemina;
public:
    MediaSegment(char *naslov = "", char *avtor = "", int vremetraenje =0, int golemina =0) {
        strcpy(this->naslov,naslov);
        strcpy(this->avtor,avtor);
        this->vremetraenje = vremetraenje;
        this->golemina = golemina;
    }
    virtual float price () = 0;
    char *getNaslov() { return naslov;}
    char *getAvtor() {return avtor;}
    int getVremetraenje () {return vremetraenje;}

/*
ostream &operator << (ostream &out, MediaSegment &mv) {
    out<<mv.getNaslov()<<" - "<<mv.getAvtor()<<" - "<<mv.getDatum()<<" - "<<mv.getVremetraenje()<<" - "<<mv.MusicVideo::price();
}
*/

};

class AudioRecording : virtual public MediaSegment {
protected:
    Format format;
    short brojKanali;
public:
//    AudioRecording a(title, author, duration, size, format, channels);
    AudioRecording(char *title = "", char *author ="", int duration =0, int _size = 0, int _format = 0, short channels = 0): MediaSegment(title,author,duration,_size) {
        this->format = (Format)_format;
        this->brojKanali = channels;
    }
    float price () { //problematichna???
        float tempProizvod = vremetraenje * brojKanali;
        if(format == (Format)3) {
            return tempProizvod + (tempProizvod*0.5);
        }
        else {
            return tempProizvod;
        }
    }
    friend ostream &operator << (ostream &out, AudioRecording &other) {
        return out<<other.naslov<<" - "<<other.avtor<<" - "<<other.vremetraenje<<" - "<<other.golemina<<" - "<<other.price();
    }
};

class VideoRecording : virtual public MediaSegment {
protected:
    int sirina;
    Kompresija kompresija;
public:
    //    VideoRecording v(title, author, duration, size, width, compression);
    VideoRecording (char *title = "", char *author = "", int duration = 0, int _size = 0, int width = 0, int _kompresija =0 ):MediaSegment(title,author,duration,_size) {
        this->sirina = width;
        this->kompresija = (Kompresija)_kompresija;
    }
    float price () {
        float tempCena = 0;
        if(sirina<=1920)
            tempCena += 100*this->vremetraenje;
        if(sirina>1920)
            tempCena += 170*this->vremetraenje;
        if(kompresija == (Kompresija)0) {
            return tempCena+(tempCena*0.5);
        }
        else if (kompresija == (Kompresija)1)
            return tempCena-(tempCena*0.10);
        else
            return tempCena;
    }
    friend ostream &operator << (ostream &out, VideoRecording &other) {
        return out<<other.naslov<<" - "<<other.avtor<<" - "<<other.vremetraenje<<" - "<<other.golemina<<" - "<<other.sirina<<" - "<<other.VideoRecording::price();
    }
};

class MusicVideo : public VideoRecording, public AudioRecording {
private:
    char datumPublikacija[9];
public:
//    MusicVideo mv(title, author, duration, size, format, channels, width, compression, publication_date);
    MusicVideo(char *title = "", char *author ="", int duration = 0,int _size = 0, int _format = 0, int channels = 0, int width =0, int compression = 0, char *publicationDate = ""){
        strcpy(naslov,title);
        strcpy(avtor,author);
        vremetraenje = duration;
        golemina = _size;
        format = (Format)_format;
        brojKanali = channels;
        sirina = width;
        kompresija = (Kompresija)compression;
        strcpy(this->datumPublikacija,publicationDate);
    }
    float price () {
        float tempSum = 0;
        tempSum += this->AudioRecording::price();
        tempSum += this->VideoRecording::price();
        if(datumPublikacija[4] == '2'){
            if(datumPublikacija[6] < '1')
                return tempSum;
            else {
                return tempSum + (tempSum*0.30);
            }
        }
        return tempSum;
    }
    char *getDatum() {return datumPublikacija;}
    friend ostream &operator << (ostream &out, MusicVideo &mv) {
        out<<mv.getNaslov()<<" - "<<mv.getAvtor()<<" - "<<mv.datumPublikacija<<" - "<<mv.getVremetraenje()<<" - "<<mv.MusicVideo::price();
    }
};

float total_price (MediaSegment **obj, int n)  {
    float tempSum = 0;
    for(int i=0;i<n;i++)
        tempSum += obj[i]->price();
    return tempSum;
}

ostream &operator << (ostream &out, MediaSegment &mds) {
    if(dynamic_cast<AudioRecording*>(&mds))
        cout<< *dynamic_cast<AudioRecording*>(&mds);
    else if(dynamic_cast<VideoRecording*>(&mds))
        cout<< *dynamic_cast<VideoRecording*>(&mds);
    else
        cout<< *dynamic_cast<MusicVideo*>(&mds);
}

MediaSegment &cheapest_music_video (MediaSegment **obj, int n)  {
    float cheapestPrice = 1000000;
    int index = 0;
    for(int i=0;i<n;i++) {
        if(dynamic_cast<MusicVideo*>(obj[i])) {
            if(obj[i]->price() < cheapestPrice) {
                cheapestPrice = obj[i]->price();
                index = i;
            }
        }
    }
    return *obj[index];
}

int main() {

    int test_case_num;
    cin>>test_case_num;


    // for MediaSegment
    char title[100];
    char author[1000];
    unsigned int size;
    unsigned int duration;


    // for AudioRecording
    //-------------------
    unsigned short channels;

    // AudioFormat:
    // 0 - mp3
    // 1 - wav
    // 2 - ogg
    // 3 - flac
    unsigned short format;


    // for VideoRecording
    //-------------------
    unsigned short width;

    // VideoCompression:
    // 0 - x264
    // 1 - Theora
    // 2 - AV1
    int compression;


    // for MusicVideo
    //-------------------
    char publication_date[9];


    if (test_case_num == 1){
        cout<<"Testing class AudioRecording and operator<<"<<std::endl;
        cin.get();
        cin.getline(title,100);
        cin.getline(author, 100);
        //cin.get();
        cin >> duration >> size;
        cin >> format >> channels;

        AudioRecording a(title, author, duration, size, format, channels);

        cout<<a;

    }

    else if (test_case_num == 2){
        cout<<"Testing class VideoRecording and operator<<"<<std::endl;
        cin.get();
        cin.getline(title,100);
        cin.getline(author, 100);
        //cin.get();
        cin >> duration >> size;
        cin >> width >> compression;

        VideoRecording v(title, author, duration, size, width, compression);

        cout<<v;

    }

    else if (test_case_num == 3){
        cout<<"Testing class MusicVideo and operator<<"<<std::endl;

        cin.get();
        cin.getline(title,100);
        cin.getline(author, 100);
        //cin.get();
        cin >> duration >> size;

        cin >> format >> channels;
        cin >> width >> compression;

        cin.get();
        cin.getline(publication_date, 9);
        MusicVideo mv(title, author, duration, size, format, channels, width, compression, publication_date);

        cout << mv;
    }

    else if (test_case_num == 4){
        cout<<"Testing function: total_price "<<std::endl;

        MediaSegment ** m;

        int num_media_segments;
        cin >> num_media_segments;

        // 1 - AudioRecording
        // 2 - VideoRecording
        // 3 - MusicVideo
        short media_type;

        m = new MediaSegment*[num_media_segments];

        for (int i=0; i<num_media_segments; i++) {

            cin >> media_type;

            cin.get();
            cin.getline(title,100);
            cin.getline(author, 100);
            //cin.get();
            cin >> duration >> size;

            switch(media_type) {
                case 1:
                    cin >> format >> channels;
                    m[i] = new AudioRecording(title, author, duration, size, format, channels);
                    break;
                case 2:
                    cin >> width >> compression;
                    m[i] = new VideoRecording(title, author, duration, size, width, compression);
                    break;
                case 3:
                    cin >> format >> channels;
                    cin >> width >> compression;
                    cin.get();
                    cin.getline(publication_date, 9);
                    m[i] = new MusicVideo(title, author, duration, size, format, channels, width, compression, publication_date);
                    break;
            }
        }

        //for (int i=0;i<num_media_segments; i++){
        //    cout << *m[i];
        //}

        cout<< "Total price is: " << total_price(m, num_media_segments);

        delete [] m;

    }
    else if (test_case_num == 5){
        cout<<"Testing function: cheapest_music_video "<<std::endl;

        MediaSegment ** m;

        int num_media_segments;
        cin >> num_media_segments;

        // 1 - AudioRecording
        // 2 - VideoRecording
        // 3 - MusicVideo
        short media_type;

        m = new MediaSegment*[num_media_segments];

        for (int i=0; i<num_media_segments; i++) {

            cin >> media_type;

            cin.get();
            cin.getline(title,100);
            cin.getline(author, 100);
            //cin.get();
            cin >> duration >> size;

            switch(media_type) {
                case 1:
                    cin >> format >> channels;
                    m[i] = new AudioRecording(title, author, duration, size, format, channels);
                    break;
                case 2:
                    cin >> width >> compression;
                    m[i] = new VideoRecording(title, author, duration, size, width, compression);
                    break;
                case 3:
                    cin >> format >> channels;
                    cin >> width >> compression;
                    cin.get();
                    cin.getline(publication_date, 9);
                    m[i] = new MusicVideo(title, author, duration, size, format, channels, width, compression, publication_date);
                    break;
            }
        }
        cout << cheapest_music_video(m, num_media_segments);

        delete [] m;
    }

    return 0;
}

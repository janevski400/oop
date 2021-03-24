//Stefan Janevski - 201117
#include<iostream>
#include<cstring>
using namespace std;

class Category {
    private:
        char name[20];
    public:
        Category (char *name = "unnamed") {
            strcpy(this->name, name);
        }
        
        ~Category(){}
        
        void print()
        {
            cout<<"Category: "<<name<<endl;
        }
};

class NewsArticle {
    private:
        Category category;
        char title[30];
    public:
        
        NewsArticle ()
        {
            strcpy(title, "untitled");
        }
        
        NewsArticle (const Category category, char *title = "untitled")
        {
            this->category = category;
            strcpy(this->title,title);
        }
        
        ~NewsArticle(){}
        
        void print()
        {
            cout<<"Article title: "<<title<<endl;
            category.print();
        }
};

class FrontPage {
    private:
        NewsArticle article;
        float price;
        int editionNumber;
    public:
        
        FrontPage () {
            editionNumber = 0;
        }
        
        FrontPage (const NewsArticle article, float price = 0, int editionNumber = 0)
        {
            this->article = article;
            this->price = price;
            this->editionNumber=editionNumber;
        }
        
        ~FrontPage(){}
        
        void print()
        {
            cout<<"Price: "<<price<<", Edition number: "<<editionNumber<<endl;
            article.print();
        }
};

int main() {
    char categoryName[20];
    char articleTitle[30];
    float price;
    int editionNumber;

    int testCase;
    cin >> testCase;


    if (testCase == 1) {
        int iter;
        cin >> iter;
        while (iter > 0) {
            cin >> categoryName;
            cin >> articleTitle;
            cin >> price;
            cin >> editionNumber;
            Category category(categoryName);
            NewsArticle article(category, articleTitle);
            FrontPage frontPage(article, price, editionNumber);
            frontPage.print();
            iter--;
        }
    }
    else if (testCase == 2) {
        cin >> categoryName;
        cin >> price;
        cin >> editionNumber;
        Category category(categoryName);
        NewsArticle article(category);
        FrontPage frontPage(article, price, editionNumber);
        frontPage.print();
    }// test case 3
    else if (testCase == 3) {
        cin >> categoryName;
        cin >> articleTitle;
        cin >> price;
        Category category(categoryName);
        NewsArticle article(category, articleTitle);
        FrontPage frontPage(article, price);
        frontPage.print();
    }
    else {
        FrontPage frontPage = FrontPage();
        frontPage.print();
    }
    return 0;
}

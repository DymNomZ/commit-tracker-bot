#include "MyBot.h"
#include <dpp/dpp.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <filesystem>
#include <Windows.h>

using namespace std;
using namespace dpp;

const string BOT_TOKEN = "TOKEN HERE vv";

//variables
const int NUMBER_OF_REPOS = 2;
string infos[4];
string current_hashes[NUMBER_OF_REPOS]; //current_hash.txt has an initial dummy string at the very first run of the program
string output[NUMBER_OF_REPOS];
int idx = 0;

void sendPM(string what_repo, cluster& bot);
void updateDiscord(int repo, cluster& bot, string mention_who, snowflake channel_id, string repo_name);

void getDetails(int repo) {

    std::ifstream inputFile("C:\\Users\\User\\Desktop\\commit-tracker-bot\\MyBot\\store_info.txt");
    if (inputFile.is_open()) {
        std::string line;
        while (getline(inputFile, line)) {
            infos[idx] = line;
            idx++;
        }
        inputFile.close();
    }
    else {
        std::cout << "Error getting info from store_info file." << std::endl;
    }

    std::ifstream get_files_changed_details("C:\\Users\\User\\Desktop\\commit-tracker-bot\\MyBot\\files_changed.txt");
    if (get_files_changed_details.is_open()) {
        string line;
        do {
            output[repo] += line;
            output[repo] += '\n';
        } while (getline(get_files_changed_details, line));
        get_files_changed_details.close();
    }
    else {
        std::cout << "Error getting info from files_changed file." << std::endl;
    }

    //reset idx
    idx = 0;
}

_Use_decl_annotations_ int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE prevInst, PWSTR cmdLine, int cmdShow)
{
    cluster bot(BOT_TOKEN);

    bot.on_log(dpp::utility::cout_logger());

    bot.on_ready([&bot](const dpp::ready_t& event) {
        
        //get current hashes
        std::ifstream get_current_hashes("C:\\Users\\User\\Desktop\\commit-tracker-bot\\MyBot\\current_hash.txt");
        if (get_current_hashes.is_open()) {
            std::string line;
            while (getline(get_current_hashes, line)) {
                current_hashes[idx] = line;
                idx++;
            }
            get_current_hashes.close();
        }
        else {
            std::cout << "Error getting hash from current_hashes file." << std::endl;
        }

        std::cout << current_hashes[0] << " " << current_hashes[1] << std::endl;

        //reset idx
        idx = 0;

        //JAVA PASSION GAME FIRST:
        std::filesystem::current_path("C:\\Users\\User\\Desktop\\j2dc");

        system("git pull");
        //sleep to allow the command to finish pulling
        Sleep(8000);

        //run git commands exe on bot folder, why? dunno I can't seem to make the git commands code to run on vs only on vs code.
        system("C:\\Users\\User\\Desktop\\commit-tracker-bot\\MyBot\\run_git_coms.exe");

        //get information and files changed details
        getDetails(0);

        //cd back to bot folder
        std::filesystem::current_path("C:\\Users\\User\\Desktop\\commit-tracker-bot\\Debug\\");

        //check if commit hashes are different
        if (current_hashes[0].compare(infos[0]) != 0) updateDiscord(0, bot, "ATTENTION @everyone!", 1285542405805703168, "j2dc");
        //else sendPM("Java Passion Game", bot);

        //NEW JAVA GAME SECOND:
        std::filesystem::current_path("C:\\Users\\User\\Desktop\\bbc");
        system("git pull");
        Sleep(8000);
        system("C:\\Users\\User\\Desktop\\commit-tracker-bot\\MyBot\\run_git_coms.exe");

        getDetails(1);

        std::filesystem::current_path("C:\\Users\\User\\Desktop\\commit-tracker-bot\\Debug\\");

        if (current_hashes[1].compare(infos[0]) != 0) updateDiscord(1, bot, "ATTENTION @everyone!", 1328599799456596032, "bbc");
        //else sendPM("New Java Game", bot);

        //update hashes
        ofstream update_current_hash("C:\\Users\\User\\Desktop\\commit-tracker-bot\\MyBot\\current_hash.txt");
        if (update_current_hash.is_open()) {

            update_current_hash << current_hashes[0] << "\n" << current_hashes[1] << endl;

            update_current_hash.close();
            cout << "Successfully updated current hash!" << endl;
        }
        else {
            cout << "Error updating current hash" << endl;
        }

        });

    bot.start(dpp::st_wait);

    return 0;
}

void sendPM(string what_repo, cluster& bot) {

    std::cout << "No new commits!" << std::endl;
    dpp::message no_commit_pm = dpp::message::message("No new commits!");
    bot.direct_message_create(279180492245565442, no_commit_pm);
    Sleep(2000);
    bot.direct_message_create(781662446304886807, no_commit_pm);
    std::cout << "Send private message to main and alt DymNomZs" << std::endl;

}

void updateDiscord(int repo, cluster& bot, string mention_who, snowflake channel_id, string repo_name) {
    //if so replace appropriate hash
    current_hashes[repo] = infos[0];

    //set IDs
    string github_id;
    string discord_id;
    string role_id;
    string name = infos[2];
    string profile;

    cout << "Name: " << name << endl;

    //Big ass if-else cause switch won't accept strings
    if (name.compare("DymNomZ") == 0 || name.compare("Dymes") == 0)
    {
        profile = "DymNomZ";
        github_id = "145899766";
        discord_id = "279180492245565442";
        role_id = "1148236835454210070";
    }
    else if (name.compare("BladeLucas") == 0 || name.compare("BladeLucas27") == 0 || name.compare("unknown") == 0)
    {
        profile = "BladeLucas";
        github_id = "115134677";
        discord_id = "481296387745775626";
        role_id = "1275694654075174965";
    }
    else if (name.compare("Seth Nathaniel") == 0 || name.compare("BreakfasteMeat") == 0 || name.compare("PC-1") == 0)
    {
        profile = "BreakfasteMeat";
        github_id = "133184897";
        discord_id = "691134401018593350";
        role_id = "1210226098214936666";
    }
    else if (name.compare("CursedSensei") == 0 || name.compare("Zillion") == 0 || name.compare("Zillion Linux") == 0)
    {
        profile = "CursedSensei";
        github_id = "102786087";
        discord_id = "413231303534837762";
        role_id = "1148218807312207872";
    }
    else if (name.compare("Fay-V") == 0)
    {
        profile = "Fay-V";
        github_id = "178550114";
        discord_id = "1147881270509060147";
        role_id = "1210225987829239808";
    }
    else if (name.compare("hnselcrck") == 0)
    {
        profile = "hnselcrck";
        github_id = "160475299";
        discord_id = "812284993614512148";
        role_id = "1210225434638159872";
    }
    else if (name.compare("Kurt") == 0 || name.compare("Icession") == 0)
    {
        profile = "Kurt";
        github_id = "167537767";
        discord_id = "590844399039021058";
        role_id = "1217084693091192853";
    }
    else if (name.compare("Joshua Sarcol") == 0 || name.compare("jjsnippets") == 0)
    {
        profile = "Joshua Sarcol";
        github_id = "144335180";
        discord_id = "751779696160538625";
        role_id = "1210226532015022101";
    }
    else if (name.compare("lance-enario") == 0 || name.compare("lance.enario") == 0)
    {
        profile = "Lance Enario";
        github_id = "178461623";
        discord_id = "598517212449472537";
        role_id = "1217084878299070524";
    }
    else if (name.compare("Pinghtdog") == 0 || name.compare("Ping") == 0)
    {
        profile = "Ping";
        github_id = "178667768";
        discord_id = "806957419958894642";
        role_id = "1210225686044868669";
    }
    else if (name.compare("siv727") == 0 || name.compare("siv-a-siv") == 0)
    {
        profile = "siv-a-siv";
        github_id = "143003088";
        discord_id = "735467108875632700";
        role_id = "1217456469302186085";
    }
    else if (name.compare("TopeMe") == 0 || name.compare("TopeQue") == 0)
    {
        profile = "TopeQue";
        github_id = "102395021";
        discord_id = "391003277111721985";
        role_id = "1148218640282423358";
    }

    std::cout << "git id: " << github_id << " discord id: " << discord_id << " role id: " << role_id << std::endl;

    string b_commit_URL = "https://github.com/DymNomZ/" + repo_name + "/commit/" + infos[0];
    string b_profile_URL = "https://github.com/" + profile;
    string b_avatar_URL = "https://avatars.githubusercontent.com/u/" + github_id + "?v=4";
    string b_commit_hash = "Commit Hash: " + infos[0];

    string_view avatar_URL = b_avatar_URL;
    string_view commit_URL = b_commit_URL;
    string_view profile_URL = b_profile_URL;
    string_view username = profile;
    string_view commit_hash = b_commit_hash;
    string_view files_changed = output[repo];

    std::cout << avatar_URL << " " << commit_URL << " " << profile_URL << " " << username << " " << commit_hash << std::endl;
    std::cout << output[repo] << std::endl;

    dpp::embed embed = dpp::embed()
        .set_color(dpp::colors::medium_sea_green)
        .set_title("Click to go to commit^")
        .set_url(commit_URL)
        .set_author(username, profile_URL, avatar_URL)
        .set_description(commit_hash)
        .set_thumbnail(avatar_URL)
        .add_field(
            "Commit Message:",
            infos[1]
        )
        .add_field(
            "Commit Date",
            infos[3]
        )
        .add_field(
            "Files changed:",
            files_changed
        );

    string mention_role = "New commit by <@&" + role_id + ">";
    dpp::message mention = dpp::message::message(channel_id, mention_who);
    dpp::message msg1 = dpp::message::message(channel_id, mention_role);
    dpp::message msg2 = dpp::message::message(channel_id, "Make sure to pull first before pushing changes!");
    dpp::message commit_embed = dpp::message::message(channel_id, embed);
    bot.co_message_create(mention);
    Sleep(2000);
    bot.co_message_create(msg1);
    Sleep(2000);
    bot.co_message_create(msg2);
    Sleep(2000);
    bot.co_message_create(commit_embed);

}

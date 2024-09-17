#include "MyBot.h"
#include <dpp/dpp.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <filesystem>

using namespace std;
using namespace dpp;

const string BOT_TOKEN = "TOKEN HERE vv";

int main()
{
    cluster bot(BOT_TOKEN);

    bot.on_log(dpp::utility::cout_logger());

    bot.on_ready([&bot](const dpp::ready_t& event) {
        //run the exe....Visual Studio C++ is picky about popen and size of array :p
        //this runs the git commands and stores the data in store_info.txt
        //current_hash has an initial dummy string at the very first run of the program
        
        //cd to repo
        std::filesystem::current_path("C:\\Users\\User\\Desktop\\Java-2D-Game-Collab");
        //run exe on bot folder
        system("C:\\Users\\User\\Desktop\\commit-tracker-bot\\MyBot\\run_git_coms.exe");

        //variables
        string infos[4];
        string current_hash, output;
        int idx = 0;

        //cd back to bot folder -> Debug to be changed
        std::filesystem::current_path("C:\\Users\\User\\Desktop\\commit-tracker-bot\\Debug\\");

        //get information
        std::ifstream inputFile("C:\\Users\\User\\Desktop\\commit-tracker-bot\\MyBot\\store_info.txt");
        if (inputFile.is_open()) {
            std::string line;
            while (getline(inputFile, line)) {
                infos[idx] = line;
                std::cout << infos[idx] << std::endl;
                idx++;
            }
            inputFile.close();
        }
        else {
            std::cout << "Error getting info from store_info file." << std::endl;
        }

        //get current hash
        std::ifstream get_current_hash("C:\\Users\\User\\Desktop\\commit-tracker-bot\\MyBot\\current_hash.txt");
        if (get_current_hash.is_open()) {
            getline(get_current_hash, current_hash);
            get_current_hash.close();
        }
        else {
            std::cout << "Error getting hash from current_hash file." << std::endl;
        }

        //get files changed details
        std::ifstream get_files_changed_details("C:\\Users\\User\\Desktop\\commit-tracker-bot\\MyBot\\files_changed.txt");
        if (get_files_changed_details.is_open()) {
            string line;
            do{
                output += line;
                output += '\n';
            }while (getline(get_files_changed_details, line));
            get_files_changed_details.close();
        }
        else {
            std::cout << "Error getting info from files_changed file." << std::endl;
        }

        std::cout << current_hash << "---" << infos[0] << std::endl;

        if(current_hash != infos[0]){
            //set IDs
            string github_id;
            string discord_id;
            string role_id;
            string name = infos[2];

            cout << "Name: " << name << endl;

            //Big ass if-else cause switch won't accept strings
            if (name.compare("DymNomz") == 0) { github_id = "145899766"; discord_id = "279180492245565442"; role_id = "1148236835454210070";}
            else if (name.compare("BladeLucas27") == 0) { github_id = "115134677"; discord_id = "481296387745775626"; role_id = "1275694654075174965";}
            else if (name.compare("BreakfasteMeat") == 0) { github_id = "133184897"; discord_id = "691134401018593350"; role_id = "1210226098214936666";}
            else if (name.compare("CursedSensei") == 0) { github_id = "102786087"; discord_id = "413231303534837762"; role_id = "1148218807312207872";}
            else if (name.compare("Fay-V") == 0) { github_id = "178550114"; discord_id = "1147881270509060147"; role_id = "1210225987829239808";}
            else if (name.compare("hnselcrck") == 0) { github_id = "160475299"; discord_id = "812284993614512148"; role_id = "1210225434638159872";}
            else if (name.compare("Icession") == 0) { github_id = "167537767"; discord_id = "590844399039021058"; role_id = "1217084693091192853";}
            else if (name.compare("jjsnippets") == 0) { github_id = "144335180"; discord_id = "751779696160538625"; role_id = "1210226532015022101";}
            else if (name.compare("lance-enario") == 0) { github_id = "178461623"; discord_id = "598517212449472537"; role_id = "1217084878299070524";}
            else if (name.compare("Pinghtdog") == 0) { github_id = "178667768"; discord_id = "806957419958894642"; role_id = "1210225686044868669";}
            else if (name.compare("siv727") == 0) { github_id = "143003088"; discord_id = "735467108875632700"; role_id = "1217456469302186085";}
            else if (name.compare("TopeMe") == 0) { github_id = "102395021"; discord_id = "391003277111721985"; role_id = "1148218640282423358";}

            std::cout << "git id: " << github_id << " discord id: " << discord_id << " role id: " << role_id << std::endl;

            string b_commit_URL = "https://github.com/DymNomZ/Java-2D-Game-Collab/commit/" + infos[0];
            string b_profile_URL = "https://github.com/" + infos[2];
            string b_avatar_URL = "https://avatars.githubusercontent.com/u/" + github_id + "?v=4";
            string b_commit_hash = "Commit Hash: " + infos[0];

            string_view avatar_URL = b_avatar_URL;
            string_view commit_URL = b_commit_URL;
            string_view profile_URL = b_profile_URL;
            string_view username = infos[2];
            string_view commit_hash = b_commit_hash;
            string_view files_changed = output;

            std::cout << avatar_URL << " " << commit_URL << " " << profile_URL << " " << username << " " << commit_hash << std::endl;
            std::cout << output << std::endl;

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
            dpp::message mention = dpp::message::message(1285542405805703168, "ATTENTION @everyone!");
            dpp::message msg1 = dpp::message::message(1285542405805703168, mention_role);
            dpp::message msg2 = dpp::message::message(1285542405805703168, "Make sure to pull first before pushing changes!");
            dpp::message commit_embed = dpp::message::message(1285542405805703168, embed);
            bot.co_message_create(mention);
            Sleep(2000);
            bot.co_message_create(msg1);
            Sleep(2000);
            bot.co_message_create(msg2);
            Sleep(2000);
            bot.co_message_create(commit_embed);

            //replace the current hash
            ofstream update_current_hash("C:\\Users\\User\\Desktop\\commit-tracker-bot\\MyBot\\current_hash.txt");
            if (update_current_hash.is_open()) {
                update_current_hash << infos[0] << endl;
                update_current_hash.close();
                cout << "Successfully updated current hash!" << endl;
            } else {
                cout << "Error updating current hash" << endl;
            }

        } else {
            std::cout << "No new commits!" << std::endl;
        }
        });

    bot.start(dpp::st_wait);

    return 0;
}
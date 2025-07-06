#include <iostream>
#include <vector>
#include "raylib.h"
#include "resource_loader.hpp"

int main()
{
    InitWindow(600, 600, "Resource Management Example");
    InitAudioDevice();

    auto pack = rm::rLdr::create_pack_buffer("MyGameData/PackedResources/my_pack.pk", "MySecret_encryption_key123");
    
    rm::rLdr::open_pack_buffer(pack);

    std::vector<char> player_img_data = rm::rLdr::get_pack_data(pack, "pack1/Player/player.png");
    std::vector<char> enemy_img_data = rm::rLdr::get_pack_data(pack, "pack1/Enemy/enemy.png");
    std::vector<char> music_data = rm::rLdr::get_pack_data(pack, "pack1/Audio/time_for_adventure.mp3");
    std::vector<char> jump_snd_data = rm::rLdr::get_pack_data(pack, "pack1/Audio/jump.wav");

    rm::rLdr::close_pack_buffer(pack);

    Image player_img = LoadImageFromMemory(".png", (unsigned char*)player_img_data.data(), player_img_data.size());
    Texture2D player_texture = LoadTextureFromImage(player_img);

    Image enemy_img = LoadImageFromMemory(".png", (unsigned char*)enemy_img_data.data(), enemy_img_data.size());
    Texture2D enemy_texture = LoadTextureFromImage(enemy_img);

    Music music = LoadMusicStreamFromMemory(".mp3", (unsigned char*)music_data.data(), music_data.size());

    Wave jump_wave = LoadWaveFromMemory(".wav", (unsigned char*)jump_snd_data.data(), jump_snd_data.size());
    Sound jump_sound = LoadSoundFromWave(jump_wave);

    PlayMusicStream(music);


    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_SPACE))
        {
            PlaySound(jump_sound);
        }
        UpdateMusicStream(music);

        BeginDrawing();
        ClearBackground(DARKBLUE);
        DrawTexture(player_texture, 300 - 64, 50, WHITE);
        DrawTexture(enemy_texture, 300 - 64, 350, WHITE);

        DrawText("Press space\nfor sound fx", 200, 250, 30, RED);

        EndDrawing();
    }

    UnloadTexture(player_texture);
    UnloadTexture(enemy_texture);

    UnloadMusicStream(music);
    UnloadSound(jump_sound);

    CloseWindow();
    CloseAudioDevice();
    
    return 0;
}
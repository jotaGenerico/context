#include "so_long_bonus.h"

void	update_animation(t_game *game)
{
	game->frame_counter++;
	if (game->frame_counter >= ANIMATION_SPEED)
	{
		game->current_frame = (game->current_frame + 1) % PLAYER_FRAMES;
		game->frame_counter = 0;
	}
}

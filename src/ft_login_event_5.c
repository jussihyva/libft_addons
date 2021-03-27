/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_login_event_5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 09:07:03 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/24 09:39:53 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

static t_loging_params		*g_loging_params;

void				set_g_loging_params_5(t_loging_params *loging_params)
{
	g_loging_params = loging_params;
	return ;
}

int					ft_log_add_fp(int fd, int level)
{
	return (log_add_callback(file_callback, fd, level));
}

void				ft_log_trace(const char *fmt, ...)
{
	t_log_event				event;

	event.fmt = fmt;
	event.file = __FILE__;
	event.line = __LINE__;
	event.level = LOG_TRACE;
	gettimeofday(&event.tv, NULL);
	lock();
	if (!g_loging_params->quiet && event.level >= g_loging_params->level)
	{
		event.fd = 2;
		va_start(event.ap, fmt);
		stdout_callback(&event);
		va_end(event.ap);
	}
	execute_login_extensions(&event, fmt);
	unlock();
	return ;
}

void				unlock(void)
{
	if (g_loging_params->lock)
	{
		g_loging_params->lock(1, g_loging_params->udata);
	}
}

void				ft_log_fatal(const char *fmt, ...)
{
	t_log_event				event;

	event.fmt = fmt;
	event.file = __FILE__;
	event.line = __LINE__;
	event.level = LOG_FATAL;
	gettimeofday(&event.tv, NULL);
	lock();
	if (!g_loging_params->quiet && event.level >= g_loging_params->level)
	{
		event.fd = 2;
		va_start(event.ap, fmt);
		stdout_callback(&event);
		va_end(event.ap);
	}
	execute_login_extensions(&event, fmt);
	unlock();
	return ;
}

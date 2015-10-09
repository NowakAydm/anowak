;*******************************************************************************;
;                                                                               ;
;                                                          :::      ::::::::    ;
;    dotemacs                                            :+:      :+:    :+:    ;
;                                                      +:+ +:+         +:+      ;
;    by: thor <thor@42.fr>                           +#+  +:+       +#+         ;
;                                                  +#+#+#+#+#+   +#+            ;
;    Created: 2013/06/18 14:01:14 by thor               #+#    #+#              ;
;    Updated: 2015/10/09 18:44:32 by anowak           ###   ########.fr        ;
;                                                                               ;
;*******************************************************************************;

; Load general features files
(setq config_files "/usr/share/emacs/site-lisp/")
(setq load-path (append (list nil config_files) load-path))

(load "list.el")
(load "string.el")
(load "comments.el")
(load "header.el")

; Set default emacs configuration
(set-language-environment "UTF-8")
(setq-default font-lock-global-modes nil)
(setq-default line-number-mode nil)
(setq-default tab-width 4)
(setq-default indent-tabs-mode t)
(global-set-key (kbd "DEL") 'backward-delete-char)
(setq-default c-backspace-function 'backward-delete-char)
(setq-default c-basic-offset 4)
(setq-default c-default-style "linux")
(setq-default tab-stop-list '(4 8 12 16 20 24 28 32 36 40 44 48 52 56 60
                             64 68 72 76 80 84 88 92 96 100 104 108 112 116 120))

; Load user configuration
(if (file-exists-p "~/.myemacs") (load-file "~/.myemacs"))

;; Enable mouse support
(unless window-system
  (require 'mouse)
  (xterm-mouse-mode t)
  (global-set-key [mouse-4] (lambda ()
                              (interactive)
                              (scroll-down 1)))
  (global-set-key [mouse-5] (lambda ()
                              (interactive)
                              (scroll-up 1)))
  (defun track-mouse (e))
  (setq mouse-sel-mode t)
)

;; Scroll one line at a time
(setq scroll-step            1
      scroll-conservatively  10000)

;; Enable mouse support
(global-set-key (kbd "<kp-0>") '"0")
(global-set-key (kbd "<kp-1>") '"1")
(global-set-key (kbd "<kp-2>") '"2")
(global-set-key (kbd "<kp-3>") '"3")
(global-set-key (kbd "<kp-4>") '"4")
(global-set-key (kbd "<kp-5>") '"5")
(global-set-key (kbd "<kp-6>") '"6")
(global-set-key (kbd "<kp-7>") '"7")
(global-set-key (kbd "<kp-8>") '"8")
(global-set-key (kbd "<kp-9>") '"9")
(global-set-key (kbd "<kp-enter>") '"
")
(global-set-key (kbd "M-o n") '".")
(global-set-key (kbd "<kp-add>") '"+")
(global-set-key (kbd "<kp-subtract>") '"-")
(global-set-key (kbd "<kp-multiply>") '"*")
(global-set-key (kbd "<kp-divide>") '"/")
(global-set-key (kbd "M-o x") '"=")


;*******************************************************************************;
(custom-set-variables
  ;; custom-set-variables was added by Custom.
  ;; If you edit it by hand, you could mess it up, so be careful.
  ;; Your init file should contain only one such instance.
  ;; If there is more than one, they won't work right.
 '(gud-gdb-command-name "gdb --annotate=1")
 '(large-file-warning-threshold nil))
(custom-set-faces
  ;; custom-set-faces was added by Custom.
  ;; If you edit it by hand, you could mess it up, so be careful.
  ;; Your init file should contain only one such instance.
  ;; If there is more than one, they won't work right.
 '(font-lock-comment-face ((((class color) (min-colors 8) (background light)) (:foreground "red")))))

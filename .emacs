;;/**
;; * AS - the open source Automotive Software on https://github.com/parai
;; *
;; * Copyright (C) 2015  AS <parai@foxmail.com>
;; *
;; * This source code is free software; you can redistribute it and/or modify it
;; * under the terms of the GNU General Public License version 2 as published by the
;; * Free Software Foundation; See <http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt>.
;; *
;; * This program is distributed in the hope that it will be useful, but
;; * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
;; * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
;; * for more details.
;; */

(setq frame-background-mode 'dark)
(set-background-color "black")
(set-foreground-color "gray")
(set-cursor-color "yellow")
(set-face-foreground 'highlight "white")
(set-face-background 'highlight "blue")
(set-face-foreground 'region "cyan")
(set-face-background 'region "blue")
(set-face-foreground 'secondary-selection "skyblue")
(set-face-background 'secondary-selection "darkblue")


(if (eq system-type 'windows-nt)
  (set-default-font "Consolas-14")
  (set-default-font "Monospace-12")
)
(setq make-backup-files nil)

(display-time)
(global-linum-mode t)
(column-number-mode t)
(show-paren-mode t)
(setq default-tab-width 4) 
(setq c-indent-level 4)
(setq c-continued-statement-offset 4)
(setq c-brace-offset -4)
(setq c-argdecl-indent 4)
(setq c-label-offset -4)
(setq c-basic-offset 4)

;;(global-set-key "\C-m" 'reindent-then-newline-and-indent)
(setq indent-tabs-mode t)
(setq standard-indent 4)

;;Create MyCppStyle
(defconst MyCppStyle
  '((c-tab-always-indent . t)
    (c-comment-only-line-offset . 0)
	(c-hanging-braces-alist . ((substatement-open after)
							   (brace-list-open)))
	(c-cleanup-list . (comment-close-slash
					   compact-empty-funcall))
    (c-offsets-alist . ((substatement-open . 0)
						(innamespace . 0)      
						(case-label      . +)
						(access-label . -)
						(inline-open . 0)
						(block-open     . 0)))
	;;    (c-echo-syntactic-information-p t)
	(setq comment-start "/*"
		  comment-end "*/")
    (setq indent-tabs-mode t))
  "My Cpp Coding Style")
(c-add-style "MyCppStyle" MyCppStyle)
;;Define own hook
(defun MyCppHook ()
  (interactive)
 ;; (company-mode)
  (setq indent-tabs-mode t)
  (setq global-hl-line-mode t)
  (c-set-style "MyCppStyle"))
(add-hook 'c++-mode-hook 'MyCppHook)
(add-hook 'c-mode-hook 'MyCppHook)

(global-font-lock-mode 1) 
(setq default-directory "~/") 
;;(set-scroll-bar-mode nil)

;;(setq inhibit-startup-message t) 
;;(setq indent-tabs-mode t)

;;solve mess encode issue of shell-mode
(ansi-color-for-comint-mode-on)

(fset 'yes-or-no-p 'y-or-n-p)

(global-set-key (kbd "M-g") 'goto-line)

(global-set-key [home] 'beginning-of-buffer)
(global-set-key [end] 'end-of-buffer)

(when (eq system-type 'windows-nt)  
  (setq find-program "gfind"))

(setq case-fold-search t)

;; display buffer name or absolute file path name in the frame title
(defun frame-title-string ()
  "Return the file name of current buffer, using ~ if under home directory"
  (let
      ((fname (or
	       (buffer-file-name (current-buffer))
	       (buffer-name)))
       (max-len 100))
    (when (string-match (getenv "HOME") fname)
      (setq fname (replace-match "~" t t fname)))
    (if (> (length fname) max-len)
	(setq fname
	      (concat "..."
		      (substring fname (- (length fname) max-len)))))
    fname))
(setq frame-title-format '("Parai - Emacs@"(:eval (frame-title-string))))

(setq ediff-split-window-function 'split-window-horizontally)

(global-set-key [f3] 
				(lambda()
				  (interactive)
				  (split-window-vertically 7)
				  (eshell)
				  )
				)
(add-hook 'c-mode-common-hook 'hs-minor-mode)

(defun make-some-files-read-only ()
  ;;"when file opened is of a certain mode, make it read only"
  (when (memq major-mode '(c-mode c++-mode tcl-mode text-mode python-mode))
    (toggle-read-only 1)))

(add-hook 'find-file-hooks 'make-some-files-read-only)


;example
;============
; (shell-command "mktags")
;  :mktags is a shell script to make tags for etags and cscope
;============
;========================================================
; used to generate TAGS and cscope.out
;========================================================
(defun mktags (RootDir)
  (interactive "DInput the RootDir:")
  ;;(if (eq system-type 'windows-nt)
  (shell-command (format "cd %s && rm -f TAGS cscope.files cscope.out && find ./ -name *.[chCH] |xargs -i etags -a {}" RootDir))
  (shell-command (format "cd %s && find ./ -name *.cpp |xargs -i etags -a {} && find ./ -name *.CPP |xargs -i etags -a {}" RootDir))
  (shell-command (format "cd %s && find ./ -name *.[chCH] -print > cscope.files && find ./ -name *.cpp -print >> cscope.files" RootDir))
  (shell-command (format "cd %s && find ./ -name *.CPP -print >> cscope.files && cscope -b -i cscope.files -f cscope.out" RootDir))
  ;;)
  (setq tags-file-name (format "%s/TAGS" RootDir))
  (message "generate TAGS and cscope.out for currend project")
				  )
(global-set-key (kbd "C-c e t") 'mktags)

;=======================================================
; used to delete TAGS and cscope.out
;=======================================================
(defun deltags()
  (interactive)
  (shell-command "rm -f TAGS cscope.files cscope.out")
  (message "delete TAGS and cscope.out for currend project")
  )
(global-set-key (kbd "C-c d e t") 'deltags)

